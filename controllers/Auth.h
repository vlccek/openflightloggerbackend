#pragma once

#include <drogon/drogon.h>
#include <drogon/HttpController.h>
#include <utils/jwt/JWT.h>
#include "argon2.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>
#include <drogon/HttpAppFramework.h>
#include "Airlines.h"
#include "Users.h"
#include "utils/crypto.h"
#include <drogon/HttpController.h>
#include <drogon/orm/DbClient.h>


using namespace drogon;
using namespace api::utils::jwt;

namespace api::v1
{
    class Auth : public HttpController<Auth>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(Auth::login, "/api/v1/auth/login", Post, Options,
                          "CorsMiddleware");
            ADD_METHOD_TO(Auth::verifyToken, "/api/v1/auth/refresh", Post, Options,
                          "CorsMiddleware", "api::v1::filters::JwtFilter");
            ADD_METHOD_TO(Auth::registerUser, "/api/v1/auth/register", Post,
                          Options, "CorsMiddleware");
        METHOD_LIST_END


        Task<> login(HttpRequestPtr req,
                     std::function<void(const HttpResponsePtr&)> callback);
        Task<> verifyToken(HttpRequestPtr request, std::function<void(const HttpResponsePtr&)> callback);
        Task<> registerUser(HttpRequestPtr request, std::function<void(const HttpResponsePtr&)> callback);
    };
}
