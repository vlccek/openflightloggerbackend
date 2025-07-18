/**
 *
 *  AirportsController.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulapiControllerBase.h"

# define V1_API  "/api/v1"

#include "Airports.h"
using namespace drogon;
using namespace drogon_model::mydatabase;
/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the airports table.
 */
namespace api::v1
{
    class RestfulapiController : public drogon::HttpController<RestfulapiController>, public RestfulapiControllerBase
    {
    public:
        METHOD_LIST_BEGIN
            ADD_METHOD_TO(RestfulapiController::getOne, V1_API"/airports/{1}", Get, Options);
            ADD_METHOD_TO(RestfulapiController::updateOne, V1_API"/airports/{1}", Put, Options);
            ADD_METHOD_TO(RestfulapiController::deleteOne, V1_API "/airports/{1}", Delete, Options);
            ADD_METHOD_TO(RestfulapiController::get, V1_API "/airports", Get, Options);
            ADD_METHOD_TO(RestfulapiController::create, V1_API"/airports", Post, Options);
            //ADD_METHOD_TO(AirportsController::update,"/airports",Put,Options);
        METHOD_LIST_END

        void getOne(const HttpRequestPtr& req,
                    std::function<void(const HttpResponsePtr&)>&& callback,
                    Airports::PrimaryKeyType&& id);
        void updateOne(const HttpRequestPtr& req,
                       std::function<void(const HttpResponsePtr&)>&& callback,
                       Airports::PrimaryKeyType&& id);
        void deleteOne(const HttpRequestPtr& req,
                       std::function<void(const HttpResponsePtr&)>&& callback,
                       Airports::PrimaryKeyType&& id);
        void get(const HttpRequestPtr& req,
                 std::function<void(const HttpResponsePtr&)>&& callback);
        void create(const HttpRequestPtr& req,
                    std::function<void(const HttpResponsePtr&)>&& callback);
    };
};
