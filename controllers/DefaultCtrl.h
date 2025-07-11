
#ifndef MOVIES_DEFAULTCTRL_H
#define MOVIES_DEFAULTCTRL_H


#pragma once

#include <drogon/HttpController.h>
#include <drogon/drogon.h>

using namespace drogon;

class DefaultCtrl : public HttpController<DefaultCtrl> {
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(DefaultCtrl::listRoutes, "/", Get);
    METHOD_LIST_END

    void listRoutes(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
};


#endif //MOVIES_DEFAULTCTRL_H
