#include "Auth.h"
#include <drogon/drogon.h>


using namespace api::v1;

using namespace drogon;
using namespace drogon_model::mydatabase;

Task<> Auth::login(const HttpRequestPtr req, std::function<void(const HttpResponsePtr&)> callback)
{
    Json::Value responseJson = *req->getJsonObject();
    Json::Value resultJson;

    // Verify if there's a missing values on body of request
    if (!responseJson.isMember("email") || !responseJson.isMember("password"))
    {
        resultJson["error"] = "Missing email or password.";
        resultJson["status"] = 0;

        callback(HttpResponse::newHttpJsonResponse(resultJson));
    }

    orm::Mapper<Users> usersMapper(app().getDbClient());


    orm::Criteria criteria("email", orm::CompareOperator::EQ, responseJson["email"].asString());

    auto res = usersMapper.findFutureOne(criteria);


    auto user = res.get();

    // Verify password
    if (const auto& hash = user.getPassword(); !verifyHash(responseJson["password"].asString(), *hash))
    {
        resultJson["error"] = "Invalid password.";
        resultJson["status"] = 0;

        LOG_INFO << "Invalid password for user: " << responseJson["email"].asString();

        callback(HttpResponse::newHttpJsonResponse(resultJson));
    }

    // Generate JWT token
    std::map<std::string, picojson::value> claims;

    std::string email = user.getEmail() ? *user.getEmail() : "";
    claims["email"] = picojson::value(email);
    claims["user_id"] = picojson::value(static_cast<int64_t>(user.getValueOfId()));

    JWT jwtGenerated = JWT::generateToken(
        claims, responseJson.isMember("remember") && responseJson["remember"].asBool());

    std::int64_t jwtExpiration = jwtGenerated.getExpiration();

    resultJson["token"] = jwtGenerated.getToken();
    resultJson["expiresAt"] = jwtExpiration;
    resultJson["status"] = 1;

    LOG_INFO << "New token for user: "
             << responseJson["email"].asString()
             << " generated successfully. Token expires at: "
             << jwtExpiration;

    LOG_DEBUG << "The token is: " << jwtGenerated.getToken();

    callback(HttpResponse::newHttpJsonResponse(resultJson));

    co_return;
}

Task<> Auth::verifyToken(const HttpRequestPtr request, std::function<void(const HttpResponsePtr&)> callback)
{
    Json::Value resultJson;

    resultJson["aud"] = request->getAttributes()->get<std::string>("jwt_aud");
    resultJson["exp"] = request->getAttributes()->get<std::int64_t>("jwt_exp");
    resultJson["iat"] = request->getAttributes()->get<std::int64_t>("jwt_iat");
    resultJson["iss"] = request->getAttributes()->get<std::string>("jwt_iss");
    resultJson["nbf"] = request->getAttributes()->get<std::int64_t>("jwt_nbf");
    resultJson["email"] = request->getAttributes()->get<std::string>("jwt_email");
    resultJson["user_id"] = request->getAttributes()->get<int64_t>("jwt_user_id");
    resultJson["jwt_debugger"] = "https://jwt.io/#debugger-io?token=" + request->getHeader("Authorization").substr(7);
    resultJson["status"] = 1;

    LOG_INFO << "Token verified successfully for user: "
             << request->getAttributes()->get<std::string>("jwt_email");


    callback(HttpResponse::newHttpJsonResponse(resultJson));
    co_return;
}

Task<> Auth::registerUser(const HttpRequestPtr request, std::function<void(const HttpResponsePtr&)> callback)
{
    Json::Value responseJson = *request->getJsonObject();
    Json::Value resultJson;

    if (!responseJson.isMember("username") || !responseJson.isMember("email") || !responseJson.isMember("password"))
    {
        resultJson["error"] = "Missing username, email, or password.";
        resultJson["status"] = 0;

        LOG_INFO << "Unsuccessfull registration attempt for user: " << responseJson["email"].asString()
                                                                    << "and username:"
                                                                    << responseJson["username"].asString();

        callback(HttpResponse::newHttpJsonResponse(resultJson));
    }

    std::string username = responseJson["username"].asString();
    std::string email = responseJson["email"].asString();


    std::string password = responseJson["password"].asString();

    std::string hashedPassword = getHash(password);

    auto client = drogon::app().getDbClient();

    try
    {
        co_await client->execSqlCoro("INSERT INTO users (username, email, password) VALUES ($1, $2, $3) RETURNING id",
                                     username, email, hashedPassword);

        resultJson["status"] = 1;
        resultJson["message"] = "User registered successfully.";

        LOG_INFO << "User registered successfully: " << username
                 << " with email: " << email;

        callback(HttpResponse::newHttpJsonResponse(resultJson));
    }
    catch (const drogon::orm::DrogonDbException& e)
    {
        LOG_INFO << "Failed to register user: " << e.base().what();
        resultJson["status"] = 0;
        resultJson["error"] = "Failed to register user: ";

        callback(HttpResponse::newHttpJsonResponse(resultJson));
    }


    co_return;
}
