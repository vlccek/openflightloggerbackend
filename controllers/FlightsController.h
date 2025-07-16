#pragma once

#include <drogon/HttpController.h>
#include "Flights.h"
#include "Users.h"
#include "filters/JwtFilter.h"

using namespace drogon;
using namespace drogon_model::mydatabase;

namespace api::v1
{
    class FlightsController : public drogon::HttpController<FlightsController>
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(FlightsController::getOne, "/api/v1/myflights/{1}", Get, Options,
                          "api::v1::filters::JwtFilter",
                          "CorsMiddleware");
            ADD_METHOD_TO(FlightsController::getAll, "/api/v1/myflights", Get, Options, "api::v1::filters::JwtFilter",
                          "CorsMiddleware");
            ADD_METHOD_TO(FlightsController::create, "/api/v1/myflights", Post, Options, "api::v1::filters::JwtFilter",
                          "CorsMiddleware");
            ADD_METHOD_TO(FlightsController::updateOne, "/api/v1/myflights/{1}", Put, Options,
                          "api::v1::filters::JwtFilter",
                          "CorsMiddleware");
            ADD_METHOD_TO(FlightsController::deleteOne, "/api/v1/myflights/{1}", Delete, Options,
                          "api::v1::filters::JwtFilter",
                          "CorsMiddleware");
            ADD_METHOD_TO(FlightsController::getLatestEditedDate, "/api/v1/myflights/latestEditedDate", Get, Options,
                          "api::v1::filters::JwtFilter",
                          "CorsMiddleware");
        METHOD_LIST_END

        Task<HttpResponsePtr> getOne(HttpRequestPtr req, Flights::PrimaryKeyType id);
        Task<HttpResponsePtr> getAll(HttpRequestPtr req);
        Task<HttpResponsePtr> updateOne(HttpRequestPtr req, Flights::PrimaryKeyType id);
        Task<HttpResponsePtr> deleteOne(HttpRequestPtr req, Flights::PrimaryKeyType id);
        Task<HttpResponsePtr> getLatestEditedDate(HttpRequestPtr req);

        void create(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);
    };
}
