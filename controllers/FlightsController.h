
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
            METHOD_ADD(FlightsController::getOne, "/{1}", Get, Options, "api::v1::filters::JwtFilter");
            METHOD_ADD(FlightsController::getAll, "", Get, Options, "api::v1::filters::JwtFilter");
            METHOD_ADD(FlightsController::create, "", Post, Options, "api::v1::filters::JwtFilter");
            METHOD_ADD(FlightsController::updateOne, "/{1}", Put, Options, "api::v1::filters::JwtFilter");
            METHOD_ADD(FlightsController::deleteOne, "/{1}", Delete, Options, "api::v1::filters::JwtFilter");
        METHOD_LIST_END

        void getOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Flights::PrimaryKeyType &&id);
        void getAll(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        void create(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
        void updateOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Flights::PrimaryKeyType &&id);
        void deleteOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Flights::PrimaryKeyType &&id);
    };
}
