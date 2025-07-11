#include "DefaultCtrl.h"
#include <drogon/drogon.h>
#include <json/json.h> // Pro sestavení JSON odpovědi (volitelné, ale hezčí)

void DefaultCtrl::listRoutes(const HttpRequestPtr &req,
                             std::function<void(const HttpResponsePtr &)> &&callback) {
    // Získání seznamu registrovaných cest
    const auto &routes = drogon::app().getHandlersInfo();


    Json::Value root;
    Json::Value routesArray(Json::arrayValue);

    for (const auto &routeInfo: routes) {
        Json::Value route;
        route["path"] = std::get<0>(routeInfo);
        route["handler"] = std::get<0>(routeInfo);
        route["method"] = std::get<2>(routeInfo);

        routesArray.append(route);
    }

    root["available_routes"] = routesArray;
    root["total_routes"] = (int) routes.size();

    // Vytvoření HTTP odpovědi
    auto resp = HttpResponse::newHttpJsonResponse(root);

    // Nastavení hlaviček (nepovinné, ale dobrá praxe)
    // resp->setContentTypeCode(CT_APPLICATION_JSON); // Již nastaveno newHttpJsonResponse

    // Odeslání odpovědi
    callback(resp);
}