// Copyright (c) 2015-2016 HyphaRunner

#include "hypharunner/hypharunner.h"
#include <chrono>
#include <iostream>
#include <thread>

#ifdef __linux__
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#endif

#include <Poco/Exception.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/ServerApplication.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/core/settings/configgenerator.h>
#include <hypha/core/settings/databasesettings.h>
#include <hypha/core/settings/hyphasettings.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>

#include "hypharunner/controller/controller.h"
#include "hypharunner/network/tcpserver.h"

using namespace Poco::Util;
using namespace hypha::plugin;
using namespace hypha::handler;
using namespace hypha::utils;
using namespace hypha::settings;
using namespace hypha::database;

void HyphaRunner::initialize(Application &self) {
  ServerApplication::initialize(self);
  Logger::info("Starting Hypha Runner!");
}

void HyphaRunner::uninitialize() {
  Logger::info("Shutting Down Hypha Runner");
  ServerApplication::uninitialize();
}

int HyphaRunner::main(const std::vector<std::string> &args) {
  if (_helpRequested) {
    return Application::EXIT_OK;
  }

  try {
    Logger::info("Starting Hypha Runner!");
    HyphaSettings::loadInstance(
        config().getString("config-file", "hypha.conf"));
    Logger::info("\nLoading Database Settings ...\n");
    DatabaseSettings::instance();
    UserDatabaseSettings::instance();
    Logger::info("Loading Database ...");
    UserDatabase::instance();

    std::string stdHandlersDir;
    std::string stdPluginsDir;
#ifdef __linux__
    stdHandlersDir = "/usr/local/lib/hyphahandlers";
    stdPluginsDir = "/usr/local/lib/hyphaplugins";
#else
    stdHandlersDir = "../hyphahandlers";
    stdPluginsDir = "../hyphaplugins";
#endif

    Logger::info("Loading Handler ...");
    HandlerLoader::instance()->loadHandlers(
        config().getString("handlersdir", stdHandlersDir));
    Logger::info("Loading Plugins ...");
    PluginLoader::instance()->loadPlugins(
        config().getString("pluginsdir", stdPluginsDir));
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
  options.addOption(Option("help", "h", "display help information")
                        .required(false)
                        .repeatable(false)
                        .callback(OptionCallback<HyphaRunner>(
                            this, &HyphaRunner::handleHelp)));
  options.addOption(Option("example", "ec", "create example config file")
                        .required(false)
                        .repeatable(false)
                        .argument("file")
                        .callback(OptionCallback<HyphaRunner>(
                            this, &HyphaRunner::handleExampleFile)));
  options.addOption(
      Option("config-file", "f", "load configuration data from a file")
          .required(false)
          .repeatable(false)
          .argument("file")
          .callback(
              OptionCallback<HyphaRunner>(this, &HyphaRunner::handleConfig)));
  options.addOption(Option("handlersdir", "hd", "location for handlers")
                        .required(false)
                        .repeatable(false)
                        .argument("dir")
                        .callback(OptionCallback<HyphaRunner>(
                            this, &HyphaRunner::handleConfig)));
  options.addOption(Option("pluginsdir", "pd", "location for plugins")
                        .required(false)
                        .repeatable(false)
                        .argument("dir")
                        .callback(OptionCallback<HyphaRunner>(
                            this, &HyphaRunner::handleConfig)));
}

void HyphaRunner::handleHelp(const std::string &name,
                             const std::string &value) {
  _helpRequested = true;
  displayHelp();
  stopOptionsProcessing();
}

void HyphaRunner::handleExampleFile(const std::string &name,
                                    const std::string &value) {
  _exampleRequested = true;
  Logger::info("Create Example Config File: " + value);
  hypha::settings::ConfigGenerator generator;
  generator.generateConfigFile(value);
  stopOptionsProcessing();
}

void HyphaRunner::handleConfig(const std::string &name,
                               const std::string &value) {
  if (name == "config-file" || name == "f") {
    Logger::info("Loading Config from File: " + value);
    config().setString("config-file", value);
  }
  if (name == "handlersdir" || name == "hd") {
    Logger::info("Loading Handlers from dir: " + value);
    config().setString("handlersdir", value);
  }
  if (name == "pluginsdir" || name == "pd") {
    Logger::info("Loading Plugins from dir: " + value);
    config().setString("pluginsdir", value);
  }
}

void HyphaRunner::displayHelp() {
  HelpFormatter helpFormatter(options());
  helpFormatter.setCommand(commandName());
  helpFormatter.setUsage("OPTIONS");
  helpFormatter.setHeader("Hypha Runner runs Plugins ...");
  helpFormatter.format(std::cout);
}

POCO_SERVER_MAIN(HyphaRunner)
