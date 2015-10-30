#include <Poco/Exception.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/HelpFormatter.h>
#include <iostream>
#include <thread>
#include <chrono>

#ifdef __linux__
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include <hypha/utils/logger.h>
#include <hypha/settings/hyphasettings.h>
#include <hypha/settings/databasesettings.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include <hypha/plugin/pluginloader.h>
#include "network/tcpserver.h"

#include <hypha/handler/handlerloader.h>
#include "controller/controller.h"

#include "hypharunner.h"

using namespace Poco::Util;
using namespace hypha::plugin;
using namespace hypha::handler;
using namespace hypha::utils;
using namespace hypha::settings;
using namespace hypha::database;

int HyphaRunner::main(const std::vector<std::string> &args) {
    if (_helpRequested)
        return EXIT_OK;

    try {
        Logger::info("Starting Hypha Runner!");
        Logger::info("\nLoading Database Settings ...\n");
        DatabaseSettings::instance();
        UserDatabaseSettings::instance();

        Logger::info("Loading Database ...");
        UserDatabase::instance();
        Logger::info("Loading Handler ...");
        HandlerLoader::instance();
        Logger::info("Loading Plugins ...");
        PluginLoader::instance();
        Logger::info("Init Handler ...");
        Controller::instance()->loadHandler();
        Logger::info("Init Plugins ...");
        Controller::instance()->loadPlugins();
        Logger::info("Starting Threads ...");
        Controller::instance()->startThreads();
        Controller::instance()->createConnections();
        TcpServer tcpServer;
        tcpServer.start();

        waitForTerminationRequest();
        Logger::info("Shutting Down Hypha Runner");
    } catch (Poco::Exception &e) {
        Logger::fatal(e.what());
    } catch (std::exception &e) {
        Logger::fatal(e.what());
    } catch (...) {
        Logger::fatal("unknown Exception");
    }

    return EXIT_OK;
}

void HyphaRunner::defineOptions(OptionSet &options) {
    Application::defineOptions(options);
    options.addOption(
        Option("help", "h", "display help information")
        .required(false)
        .repeatable(false)
        .callback(OptionCallback<HyphaRunner>(this, &HyphaRunner::handleHelp)));
    options.addOption(
        Option("config-file", "f", "load configuration data from a file")
        .required(false)
        .repeatable(true)
        .argument("file")
        .callback(OptionCallback<HyphaRunner>(this, &HyphaRunner::handleConfig)));
}

void HyphaRunner::handleHelp(const std::string &name, const std::string &value) {
    _helpRequested = true;
    displayHelp();
    stopOptionsProcessing();
}

void HyphaRunner::handleConfig(const std::string &name, const std::string &value) {
    Logger::info("Loading Config from File: " + value);
    HyphaSettings::loadInstance(value);
}

void HyphaRunner::displayHelp() {
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader(
        "Hypha Runner runs Plugins ...");
    helpFormatter.format(std::cout);
}

POCO_SERVER_MAIN(HyphaRunner)
