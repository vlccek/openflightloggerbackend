
#include "FlightsController.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>

using namespace api::v1;

void FlightsController::getOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Flights::PrimaryKeyType &&id)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();
    drogon::orm::Mapper<Flights> mapper(dbClientPtr);
    mapper.findByPrimaryKey(id, [callback, user_id](const Flights &flight) {
        if (*flight.getUserId() != user_id)
        {
            Json::Value ret;
            ret["error"] = "Forbidden";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k403Forbidden);
            callback(resp);
            return;
        }
        Json::Value ret;
        ret.append(flight.toJson());
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        callback(resp);
    }, [callback](const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    });
}

void FlightsController::getAll(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();
    drogon::orm::Mapper<Flights> mapper(dbClientPtr);
    mapper.findBy(drogon::orm::Criteria("user_id", drogon::orm::CompareOperator::EQ, user_id), [callback](const std::vector<Flights> &flights) {
        Json::Value ret;
        for (const auto &flight : flights)
        {
            ret.append(flight.toJson());
        }
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        callback(resp);
    }, [callback](const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    });
}

void FlightsController::create(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto jsonPtr = req->getJsonObject();
    if (!jsonPtr)
    {
        Json::Value ret;
        ret["error"] = "No json object is found in the request";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    try
    {
        Flights flight(*jsonPtr);
        flight.setUserId(user_id);
        auto dbClientPtr = drogon::app().getDbClient();
        drogon::orm::Mapper<Flights> mapper(dbClientPtr);
        mapper.insert(flight, [callback](const Flights &newFlight) {
            Json::Value ret;
            ret.append(newFlight.toJson());
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            callback(resp);
        }, [callback](const drogon::orm::DrogonDbException &e) {
            Json::Value ret;
            ret["error"] = e.base().what();
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            callback(resp);
        });
    }
    catch (const Json::Exception &e)
    {
        Json::Value ret;
        ret["error"] = "Field type error";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
    }
}

void FlightsController::updateOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Flights::PrimaryKeyType &&id)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();
    drogon::orm::Mapper<Flights> mapper(dbClientPtr);
    mapper.findByPrimaryKey(id, [callback, user_id, req, id](const Flights &flight) {
        if (*flight.getUserId() != user_id)
        {
            Json::Value ret;
            ret["error"] = "Forbidden";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k403Forbidden);
            callback(resp);
            return;
        }

        auto jsonPtr = req->getJsonObject();
        if (!jsonPtr)
        {
            Json::Value ret;
            ret["error"] = "No json object is found in the request";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }

        try
        {
            Flights flightUpdate(*jsonPtr);
            flightUpdate.setId(id);
            flightUpdate.setUserId(user_id);
            flightUpdate.setEditedAt(trantor::Date::now());
            auto dbClientPtr = drogon::app().getDbClient();
            drogon::orm::Mapper<Flights> mapper(dbClientPtr);
            mapper.update(flightUpdate, [callback](const size_t count) {
                Json::Value ret;
                ret["message"] = "Updated successfully";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                callback(resp);
            }, [callback](const drogon::orm::DrogonDbException &e) {
                Json::Value ret;
                ret["error"] = e.base().what();
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k500InternalServerError);
                callback(resp);
            });
        }
        catch (const Json::Exception &e)
        {
            Json::Value ret;
            ret["error"] = "Field type error";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
        }
    }, [callback](const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    });
}

void FlightsController::deleteOne(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, Flights::PrimaryKeyType &&id)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();
    drogon::orm::Mapper<Flights> mapper(dbClientPtr);
    mapper.findByPrimaryKey(id, [callback, user_id, id](const Flights &flight) {
        if (*flight.getUserId() != user_id)
        {
            Json::Value ret;
            ret["error"] = "Forbidden";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k403Forbidden);
            callback(resp);
            return;
        }

        auto dbClientPtr = drogon::app().getDbClient();
        drogon::orm::Mapper<Flights> mapper(dbClientPtr);
        mapper.deleteByPrimaryKey(id, [callback](const size_t count) {
            Json::Value ret;
            ret["message"] = "Deleted successfully";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            callback(resp);
        }, [callback](const drogon::orm::DrogonDbException &e) {
            Json::Value ret;
            ret["error"] = e.base().what();
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            callback(resp);
        });
    }, [callback](const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    });
}
