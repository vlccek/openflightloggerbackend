#include "FlightsController.h"
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>

using namespace api::v1;

Task<HttpResponsePtr> FlightsController::getOne(HttpRequestPtr req, Flights::PrimaryKeyType id)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();

    try {
        auto result = co_await dbClientPtr->execSqlCoro("SELECT * FROM flights WHERE id = $1 AND user_id = $2", id, user_id);
        if (result.empty()) {
            Json::Value ret;
            ret["error"] = "Flight not found or forbidden";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k404NotFound);
            co_return resp;
        }
        Json::Value ret;
        ret.append(Flights(result[0]).toJson());
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    } catch (const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

Task<HttpResponsePtr> FlightsController::getAll(HttpRequestPtr req)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();

    std::string sql = "SELECT * FROM flights WHERE user_id = $1";
    std::vector<std::string> params;
    params.push_back(std::to_string(user_id));

    auto lastEdited = req->getParameter("lastEdited");
    if (!lastEdited.empty()) {
        sql += " AND edited_at > $2";
    }

    try {
        drogon::orm::Result result = lastEdited.empty() ?
                                     co_await dbClientPtr->execSqlCoro(sql, user_id) :
                                     co_await dbClientPtr->execSqlCoro(sql, user_id, lastEdited);

        Json::Value ret;
        for (const auto &row : result) {
            ret.append(Flights(row).toJson());
        }
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    } catch (const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

Task<HttpResponsePtr> FlightsController::create(HttpRequestPtr req)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto jsonPtr = req->getJsonObject();
    if (!jsonPtr)
    {
        Json::Value ret;
        ret["error"] = "No json object is found in the request";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    }

    try
    {
        Flights flight(*jsonPtr);
        flight.setUserId(user_id);
        flight.setEditedAt(trantor::Date::now()); // Set edited_at on creation

        // Assuming 'flight_number' and 'flight_reason' are not optional and always present in the JSON
        co_await drogon::app().getDbClient()->execSqlCoro("INSERT INTO flights (user_id, flight_number, flight_reason, edited_at) VALUES ($1, $2, $3, $4)",
                                          user_id, flight.getValueOfFlightNumber(), flight.getValueOfFlightReason(), flight.getValueOfEditedAt());

        Json::Value ret;
        ret.append(flight.toJson());
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    }
    catch (const Json::Exception &e)
    {
        Json::Value ret;
        ret["error"] = "Field type error: " + std::string(e.what());
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    } catch (const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

Task<HttpResponsePtr> FlightsController::updateOne(HttpRequestPtr req, Flights::PrimaryKeyType id)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();

    try {
        auto existingFlightResult = co_await dbClientPtr->execSqlCoro("SELECT * FROM flights WHERE id = $1 AND user_id = $2", id, user_id);
        if (existingFlightResult.empty()) {
            Json::Value ret;
            ret["error"] = "Flight not found or forbidden";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k404NotFound);
            co_return resp;
        }

        auto jsonPtr = req->getJsonObject();
        if (!jsonPtr)
        {
            Json::Value ret;
            ret["error"] = "No json object is found in the request";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k400BadRequest);
            co_return resp;
        }

        Flights flightUpdate(*jsonPtr);
        flightUpdate.setId(id);
        flightUpdate.setUserId(user_id);
        flightUpdate.setEditedAt(trantor::Date::now());

        // Assuming 'flight_number' and 'flight_reason' are not optional and always present in the JSON
        co_await dbClientPtr->execSqlCoro("UPDATE flights SET flight_number = $1, flight_reason = $2, edited_at = $3 WHERE id = $4 AND user_id = $5",
                                          flightUpdate.getValueOfFlightNumber(), flightUpdate.getValueOfFlightReason(), flightUpdate.getValueOfEditedAt(), id, user_id);

        Json::Value ret;
        ret["message"] = "Updated successfully";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    }
    catch (const Json::Exception &e)
    {
        Json::Value ret;
        ret["error"] = "Field type error: " + std::string(e.what());
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        co_return resp;
    } catch (const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

Task<HttpResponsePtr> FlightsController::deleteOne(HttpRequestPtr req, Flights::PrimaryKeyType id)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();

    try {
        auto existingFlightResult = co_await dbClientPtr->execSqlCoro("SELECT id FROM flights WHERE id = $1 AND user_id = $2", id, user_id);
        if (existingFlightResult.empty()) {
            Json::Value ret;
            ret["error"] = "Flight not found or forbidden";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k404NotFound);
            co_return resp;
        }

        co_await dbClientPtr->execSqlCoro("DELETE FROM flights WHERE id = $1 AND user_id = $2", id, user_id);

        Json::Value ret;
        ret["message"] = "Deleted successfully";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    } catch (const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}

Task<HttpResponsePtr> FlightsController::getLatestEditedDate(HttpRequestPtr req)
{
    auto user_id = req->getAttributes()->get<int>("user_id");
    auto dbClientPtr = drogon::app().getDbClient();

    try {
        auto result = co_await dbClientPtr->execSqlCoro("SELECT MAX(edited_at) FROM flights WHERE user_id = $1", user_id);
        Json::Value ret;
        if (!result.empty() && !result[0][0].isNull()) {
            ret["latestEditedDate"] = result[0][0].as<std::string>();
        } else {
            ret["latestEditedDate"] = Json::Value(); // Or some default like "null" or empty string
        }
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        co_return resp;
    } catch (const drogon::orm::DrogonDbException &e) {
        Json::Value ret;
        ret["error"] = e.base().what();
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        co_return resp;
    }
}