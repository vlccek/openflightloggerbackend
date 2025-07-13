#include "Auth.h"
#include <drogon/drogon.h>


using namespace api::v1;

using namespace drogon;
using namespace drogon_model::mydatabase;

void Auth::getToken(const HttpRequestPtr& request, std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value responseJson = *request->getJsonObject();
    Json::Value resultJson;

    // Verify if there's a missing values on body of request
    if (!responseJson.isMember("email") || !responseJson.isMember("password"))
    {
        resultJson["error"] = "Missing email or password.";
        resultJson["status"] = 0;

        return callback(HttpResponse::newHttpJsonResponse(resultJson));
    }

    orm::Mapper<Users> usersMapper(drogon::app().getDbClient());


    orm::Criteria criteria("email", orm::CompareOperator::EQ, responseJson["email"].asString());

    usersMapper.findOne(criteria,
                      [responseJson, callback, &resultJson](const Users& user)
                      {
                          auto hash = user.getPassword();
                          // Verify password
                          if (!verifyHash(responseJson["password"].asString(), *hash))
                          {
                              resultJson["error"] = "Invalid password.";
                              resultJson["status"] = 0;
                              return callback(HttpResponse::newHttpJsonResponse(resultJson));
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
                          resultJson["expiresIn"] = jwtExpiration - std::chrono::duration_cast<std::chrono::seconds>(
                              std::chrono::system_clock::now().time_since_epoch()).count();
                          resultJson["expiresAt"] = jwtExpiration;
                          resultJson["status"] = 1;

                          return callback(HttpResponse::newHttpJsonResponse(resultJson));
                      },
                      [callback, &resultJson](const orm::DrogonDbException& e)
                      {
                          resultJson["error"] = "Database error: " + std::string(e.base().what());
                          resultJson["status"] = 0;
                          return callback(HttpResponse::newHttpJsonResponse(resultJson));
                      });

}

void Auth::verifyToken(const HttpRequestPtr& request, std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value resultJson;

    resultJson["aud"] = request->getAttributes()->get<std::string>("jwt_aud");
    resultJson["exp"] = request->getAttributes()->get<std::int64_t>("jwt_exp");
    resultJson["iat"] = request->getAttributes()->get<std::int64_t>("jwt_iat");
    resultJson["iss"] = request->getAttributes()->get<std::string>("jwt_iss");
    resultJson["nbf"] = request->getAttributes()->get<std::int64_t>("jwt_nbf");
    resultJson["email"] = request->getAttributes()->get<std::string>("jwt_email");
    resultJson["jwt_debugger"] = "https://jwt.io/#debugger-io?token=" + request->getHeader("Authorization").substr(7);
    resultJson["status"] = 1;

    return callback(HttpResponse::newHttpJsonResponse(resultJson));
}

void Auth::registerUser(const HttpRequestPtr& request, std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value responseJson = *request->getJsonObject();
    Json::Value resultJson;

    if (!responseJson.isMember("username") || !responseJson.isMember("email") || !responseJson.isMember("password"))
    {
        resultJson["error"] = "Missing username, email, or password.";
        resultJson["status"] = 0;
        return callback(HttpResponse::newHttpJsonResponse(resultJson));
    }

    std::string username = responseJson["username"].asString();
    std::string email = responseJson["email"].asString();


    std::string password = responseJson["password"].asString();

    std::string hashedPassword = getHash(password);

    auto client = drogon::app().getDbClient();
    client->execSqlAsync("INSERT INTO users (username, email, password) VALUES ($1, $2, $3) RETURNING id",
                         [&](const drogon::orm::Result& result)
                         {
                             resultJson["status"] = 1;
                             resultJson["message"] = "User registered successfully.";
                             callback(HttpResponse::newHttpJsonResponse(resultJson));
                         },
                         [&](const drogon::orm::DrogonDbException& e)
                         {
                             resultJson["status"] = 0;
                             resultJson["error"] = "Failed to register user: " + std::string(e.base().what());
                             callback(HttpResponse::newHttpJsonResponse(resultJson));
                         },
                         username, email, hashedPassword);
}
