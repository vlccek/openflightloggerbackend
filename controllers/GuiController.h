#pragma once

#include <drogon/HttpController.h>
#include "models/Users.h"
#include "utils/crypto.h"
#include "utils/jwt/JWT.h"

using namespace drogon;
using namespace drogon_model::mydatabase;

namespace api::v1
{
    class GuiController : public HttpController<GuiController>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(GuiController::showLoginPage, "/gui/login", Get);
            ADD_METHOD_TO(GuiController::handleLogin, "/gui/login", Post);
            ADD_METHOD_TO(GuiController::showRegisterPage, "/gui/register", Get);
            ADD_METHOD_TO(GuiController::handleRegister, "/gui/register", Post);
            ADD_METHOD_TO(GuiController::showAccountPage, "/gui/account/{1}", Get);
        METHOD_LIST_END

        // Non-coroutine methods
        void showLoginPage(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);
        void showRegisterPage(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

        // Coroutine methods
        Task<HttpResponsePtr> handleLogin(HttpRequestPtr req);
        Task<HttpResponsePtr> handleRegister(HttpRequestPtr req);
        Task<HttpResponsePtr> showAccountPage(HttpRequestPtr req, int userId);
    };
}
