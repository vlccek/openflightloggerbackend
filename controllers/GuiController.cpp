#include "GuiController.h"
#include <drogon/orm/DbClient.h>

// Standard, non-coroutine methods for serving static pages
void api::v1::GuiController::showLoginPage(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto resp = HttpResponse::newHttpViewResponse("Login.csp");
    callback(resp);
}

void api::v1::GuiController::showRegisterPage(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto resp = HttpResponse::newHttpViewResponse("Register.csp");
    callback(resp);
}

// Coroutine-based methods for handling form submissions and dynamic content
Task<HttpResponsePtr> api::v1::GuiController::handleLogin(HttpRequestPtr req)
{
    auto params = req->getParameters();
    std::string email = params["email"];
    std::string password = params["password"];

    auto client = app().getDbClient();
    try {
        auto result = co_await client->execSqlCoro("SELECT * FROM users WHERE email = $1", email);
        if (result.size() == 1) {
            auto user = Users(result[0]);
            if (verifyHash(password, *user.getPassword())) {
                co_return HttpResponse::newRedirectionResponse("/gui/account/" + std::to_string(user.getValueOfId()));
            } else {
                HttpViewData data;
                data.insert("error", std::string("Invalid credentials"));
                co_return HttpResponse::newHttpViewResponse("Login.csp", data);
            }
        } else {
            HttpViewData data;
            data.insert("error", std::string("Invalid credentials"));
            co_return HttpResponse::newHttpViewResponse("Login.csp", data);
        }
    } catch (const drogon::orm::DrogonDbException &e) {
        HttpViewData data;
        data.insert("error", std::string("Database error: ") + e.base().what());
        co_return HttpResponse::newHttpViewResponse("Login.csp", data);
    }
}

Task<HttpResponsePtr> api::v1::GuiController::handleRegister(HttpRequestPtr req)
{
    auto params = req->getParameters();
    std::string username = params["username"];
    std::string email = params["email"];
    std::string password = params["password"];

    std::string hashedPassword = getHash(password);

    try {
        auto client = drogon::app().getDbClient();
        co_await client->execSqlCoro("INSERT INTO users (username, email, password) VALUES ($1, $2, $3)", username, email, hashedPassword);
        co_return HttpResponse::newRedirectionResponse("/gui/login");
    } catch (const drogon::orm::DrogonDbException &e) {
        HttpViewData data;
        data.insert("error", std::string("Registration failed: ") + e.base().what());
        co_return HttpResponse::newHttpViewResponse("Register.csp", data);
    }
}

Task<HttpResponsePtr> api::v1::GuiController::showAccountPage(HttpRequestPtr req, int userId)
{
    auto client = app().getDbClient();
    try {
        auto result = co_await client->execSqlCoro("SELECT * FROM users WHERE id = $1", userId);
        if (result.size() == 1) {
            auto user = Users(result[0]);
            HttpViewData data;
            data.insert("user", user);
            co_return HttpResponse::newHttpViewResponse("Account.csp", data);
        } else {
            co_return HttpResponse::newNotFoundResponse();
        }
    } catch (const drogon::orm::DrogonDbException &e) {
        // Log error e.base().what()
        co_return HttpResponse::newNotFoundResponse();
    }
}
