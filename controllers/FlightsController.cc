#include "FlightsController.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>

using namespace api::v1;

Task<HttpResponsePtr> FlightsController::getOne(HttpRequestPtr req, Flights::PrimaryKeyType id)
{
    LOG_DEBUG << "Attempting to get flight with ID: " << id << " for user_id: " << req->getAttributes()->get<
        int>("user_id");
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();

    try
    {
        auto result = co_await dbClientPtr->execSqlCoro("SELECT * FROM flights WHERE id = $1 AND user_id = $2", id,
                                                        user_id);
        if (result.empty())
        {
            LOG_INFO << "Flight with ID: " << id << " not found or forbidden for user_id: " << user_id;
            Json::Value ret;
            ret["error"] = "Flight not found or forbidden";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k404NotFound);
            co_return resp;
        }
        Json::Value ret;
        ret.append(Flights(result[0]).toJson());
        LOG_DEBUG << "Successfully retrieved flight with ID: " << id << " for user_id: " << user_id;
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException& e)
    {
        LOG_INFO << "Database error while getting flight with ID: " << id << " for user_id: " << user_id << ". Error: "
 << e.base().what();
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

Task<HttpResponsePtr> FlightsController::getAll(HttpRequestPtr req)
{
    auto user_id = req->getAttributes()->get<int64_t>("jwt_user_id");

    LOG_DEBUG << "Attempting to get all flights of user " << user_id;

    auto dbClientPtr = drogon::app().getDbClient();

    std::string sql = "SELECT * FROM flights WHERE user_id = $1 AND edited_at > $2";

    auto lastEdited = req->getParameter("lastEdited");
    if (lastEdited.empty())
    {
        LOG_DEBUG << "lastEdited parameter is empty, using default value.";
        lastEdited = "1970-01-01T00:00:00Z";
    }
    else
    {
        LOG_DEBUG << "Using the lastEdited parameter: " << lastEdited;
    }

    try
    {
        drogon::orm::Result result = co_await dbClientPtr->execSqlCoro(sql, std::to_string(user_id), lastEdited);

        Json::Value ret;
        for (const auto& row : result)
        {
            ret.append(Flights(row).toJson());
        }
        LOG_DEBUG << "Successfully retrieved " << result.size() << " flights for user_id: " << user_id;

        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException& e)
    {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);

        LOG_INFO << "Database error while getting all flights for user_id: " << user_id << ". Error: " << e.base().
what();
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

void FlightsController::create(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto user_id = req->getAttributes()->get<int64_t>("jwt_user_id");
    auto jsonPtr = req->getJsonObject();

    LOG_DEBUG << "Attempting to create flight for user_id: " << user_id;
    if (!jsonPtr)
    {
        LOG_INFO << "Failed to create flight for user_id: " << user_id << ". No JSON object found in request.";
        Json::Value ret;
        ret["error"] = "No json object is found in the request";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    try
    {
        Flights flight(*jsonPtr); // This will throw Json::Exception if required fields are missing
        flight.setUserId(user_id);
        flight.setEditedAt(trantor::Date::now()); // Set edited_at on creation

        drogon::orm::Mapper<Flights> mapper(drogon::app().getDbClient());
        mapper.insert(flight,
                      [callback, user_id](const Flights& newFlight)
                      {
                          LOG_DEBUG << "Flight created successfully with ID: " << newFlight.getValueOfId() <<
 " for user_id: " << user_id;
                          auto resp = HttpResponse::newHttpJsonResponse(newFlight.toJson());
                          resp->setStatusCode(k200OK);
                          callback(resp);
                      },
                      [callback, user_id, req](const drogon::orm::DrogonDbException& e)
                      {
                          LOG_ERROR << "Database error while creating flight for user_id: " << user_id << ". Error: " <<
                              e.base().what() << ". Request body: " << req->body();
                          Json::Value ret;
                          ret["error"] = e.base().what();
                          auto resp = HttpResponse::newHttpJsonResponse(ret);
                          resp->setStatusCode(k500InternalServerError);
                          callback(resp);
                      });
    }
    catch (const Json::Exception& e)
    {
        LOG_INFO << "Failed to create flight for user_id: " << user_id << ". JSON parsing error: " << e.what() <<
 ". Request body: " << req->body();
        Json::Value ret;
        ret["error"] = "Field type error: " + std::string(e.what());
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
    }
}

Task<HttpResponsePtr> FlightsController::updateOne(HttpRequestPtr req, Flights::PrimaryKeyType id)
{
    auto user_id = req->getAttributes()->get<int64_t>("jwt_user_id");

    auto dbClientPtr = drogon::app().getDbClient();
    auto jsonPtr = req->getJsonObject();


    Flights flightUpdate(*jsonPtr);
    flightUpdate.setId(id);
    flightUpdate.setUserId(user_id);
    flightUpdate.setEditedAt(trantor::Date::now());


    drogon::orm::Mapper<Flights> mapper(dbClientPtr);

    try
    {
        auto update = mapper.updateFuture(flightUpdate);
        auto update_values = update.get();

        Json::Value ret;
        ret.append(Flights(flightUpdate).toJson());
        LOG_DEBUG << "Flight with ID: " << id << " updated successfully for user_id: " << user_id << "Update values" <<
 update_values;
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    }
    catch (const Json::Exception& e)
    {
        LOG_INFO << "Failed to update flight with ID: " << id << " for user_id: " << user_id << ". JSON parsing error: "
 << e.what() << ". Request body: " << req->body();
        Json::Value ret;
        ret["error"] = "Field type error: " + std::string(e.what());
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException& e)
    {
        LOG_INFO << "Database error while updating flight with ID: " << id << " for user_id: " << user_id << ". Error: "
 << e.base().what() << ". Request body: " << req->body();
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

Task<HttpResponsePtr> FlightsController::deleteOne(HttpRequestPtr req, Flights::PrimaryKeyType id)
{
    LOG_DEBUG << "Attempting to delete flight with ID: " << id << " for user_id: " << req->getAttributes()->get<
        int>("user_id");
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();

    try
    {
        auto existingFlightResult = co_await dbClientPtr->execSqlCoro(
            "SELECT id FROM flights WHERE id = $1 AND user_id = $2", id, user_id);
        if (existingFlightResult.empty())
        {
            LOG_INFO << "Flight with ID: " << id << " not found or forbidden for user_id: " << user_id;
            Json::Value ret;
            ret["error"] = "Flight not found or forbidden";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k404NotFound);
            co_return resp;
        }

        co_await dbClientPtr->execSqlCoro("DELETE FROM flights WHERE id = $1 AND user_id = $2", id, user_id);

        Json::Value ret;
        ret["message"] = "Deleted successfully";
        LOG_DEBUG << "Flight with ID: " << id << " deleted successfully for user_id: " << user_id;
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException& e)
    {
        LOG_INFO << "Database error while deleting flight with ID: " << id << " for user_id: " << user_id << ". Error: "
 << e.base().what();
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

Task<HttpResponsePtr> FlightsController::getLatestEditedDate(HttpRequestPtr req)
{
    LOG_DEBUG << "Attempting to get latest edited date for user_id: " << req->getAttributes()->get<int>("user_id");
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();

    try
    {
        auto result = co_await dbClientPtr->execSqlCoro("SELECT MAX(edited_at) FROM flights WHERE user_id = $1",
                                                        user_id);
        Json::Value ret;
        if (!result.empty() && !result[0][0].isNull())
        {
            ret["latestEditedDate"] = result[0][0].as<std::string>();
            LOG_DEBUG << "Successfully retrieved latest edited date for user_id: " << user_id << ": " << ret[
                "latestEditedDate"].asString();
        }
        else
        {
            ret["latestEditedDate"] = Json::Value(); // Or some default like "null" or empty string
            LOG_DEBUG << "No latest edited date found for user_id: " << user_id;
        }
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException& e)
    {
        LOG_INFO << "Database error while getting latest edited date for user_id: " << user_id << ". Error: " << e.
base().what();
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}
