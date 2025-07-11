#include <drogon/drogon.h>


void printControllerRoutes()
{
    const auto& handlersInfo = drogon::app().getHandlersInfo();
    if (handlersInfo.empty())
    {
        LOG_INFO << "No controller routes registered.";
        return;
    }

    std::ostringstream ss;
    ss << "Registered controller routes:\n";

    for (const auto& handlerTuple : handlersInfo)
    {
        const std::string& path = std::get<0>(handlerTuple);
        drogon::HttpMethod method = std::get<1>(handlerTuple);
        const std::string& handlerName = std::get<2>(handlerTuple);
        ss << "  Path: " << path
            << " | Method: " << drogon::to_string(method)
            << " | Handler: " << handlerName << '\n';
    }

    LOG_INFO << ss.str();
}


void printAppSettings()
{
    auto& app = drogon::app();


    std::ostringstream ss;
    ss << "Drogon server is starting with the following settings:\n";

    ss << "  Thread number: " << app.getThreadNum() << "\n";

    ss << "Server settings:";
    ss << "\n\t";
    ss << "  Thread number: " << app.getThreadNum();
    ss << "\n\t";
    ss << "  Document root: " << app.getDocumentRoot();
    ss << "\n\t";
    ss << "  Listening IP: " << app.getCustomConfig()["address"].asString();
    ss << "\n\t";
    ss << "  Listening port: " << app.getCustomConfig()["port"].asInt();
    ss << "\n\t";
    ss << "  Log level: " << app.getCustomConfig()["log_level"].asString();
    ss << "\n\t";
    ss << "Whole logfile:" << app.getCustomConfig();


    LOG_INFO << ss.str();
}


int main()
{
    //Set HTTP listener address and port
    // drogon::app().addListener("0.0.0.0", 5555);
    //Load config file
    drogon::app().loadConfigFile("../config.json");

    drogon::app().registerBeginningAdvice([]()
    {
        printControllerRoutes(); // Here you can change to your controller's name
        printAppSettings();
    });

    //drogon::app().loadConfigFile("../config.yaml");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
