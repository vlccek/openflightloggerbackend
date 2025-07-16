#include <drogon/drogon.h>
#include <drogon/HttpClient.h>
#include <drogon/drogon_test.h>
#include <json/json.h>

DROGON_TEST(AuthTest)
{
    auto db_client = drogon::app().getDbClient();

    // Clean up any test data from previous runs
    REQUIRE_NOTHROW(db_client->execSqlSync("DELETE FROM users WHERE email = 'test@example.com'"));

    // Test registration
    auto client = drogon::HttpClient::newHttpClient("http://127.0.0.1:8080");
    Json::Value request_json;
    request_json["username"] = "testuser";
    request_json["email"] = "test@example.com";
    request_json["password"] = "password123";
    auto req = drogon::HttpRequest::newHttpJsonRequest(request_json);
    req->setMethod(drogon::Post);
    req->setPath("/api/v1/auth/register");

    auto resp_pair = client->sendRequest(req);

    REQUIRE(resp_pair.first == drogon::ReqResult::Ok);
    auto resp = resp_pair.second;
    LOG_INFO << "Response: " << resp->getBody();
    REQUIRE(resp->statusCode() == drogon::k200OK);
    auto json = resp->getJsonObject();
    REQUIRE(json);
    CHECK((*json)["status"].asInt() == 1);

    // Test login
    Json::Value login_json;
    login_json["email"] = "test@example.com";
    login_json["password"] = "password123";
    req = drogon::HttpRequest::newHttpJsonRequest(login_json);
    req->setMethod(drogon::Post);
    req->setPath("/api/v1/auth/login");

    resp_pair = client->sendRequest(req);
    REQUIRE(resp_pair.first == drogon::ReqResult::Ok);
    resp = resp_pair.second;
    REQUIRE(resp->statusCode() == drogon::k200OK);
    json = resp->getJsonObject();
    REQUIRE(json);
    CHECK((*json)["status"].asInt() == 1);
    CHECK((*json)["token"].asString().length() > 0);

    std::string token = (*json)["token"].asString();

    // Test token verification
    req = drogon::HttpRequest::newHttpRequest();
    req->setMethod(drogon::Post);
    req->setPath("/api/v1/auth/refresh");
    req->addHeader("Authorization", "Bearer " + token);

    resp_pair = client->sendRequest(req);
    REQUIRE(resp_pair.first == drogon::ReqResult::Ok);
    resp = resp_pair.second;
    REQUIRE(resp->statusCode() == drogon::k200OK);
    json = resp->getJsonObject();
    REQUIRE(json);
    CHECK((*json)["status"].asInt() == 1);
    CHECK((*json)["email"].asString() == "test@example.com");

    // Clean up test data
    REQUIRE_NOTHROW(db_client->execSqlSync("DELETE FROM users WHERE email = 'test@example.com'"));
}