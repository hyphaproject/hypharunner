// Copyright (c) 2015-2016 Hypha

#include "hypharunner/controller/controller.h"
#include <hypha/controller/connection.h>
#include <hypha/core/database/database.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>
#include "hypharunner/controller/connection.h"

#include <mutex>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>

using namespace hypha::utils;
using namespace hypha::plugin;
using namespace hypha::handler;
using namespace hypha::database;

Controller *Controller::singleton = nullptr;

Controller::Controller() {}

Controller::~Controller() {}

Controller *Controller::instance() {
  static std::mutex mutex;
  if (!singleton) {
    mutex.lock();

    if (!singleton) singleton = new Controller();
    mutex.unlock();
  }

  return singleton;
}

void Controller::loadHandler() {
  HandlerLoader::instance()->loadLocalInstances();
}

void Controller::loadPlugins() {
  PluginLoader::instance()->loadLocalInstances();
}

void Controller::createConnections() {
  hypha::controller::Connection con(Database::instance());
  for (std::tuple<std::string, std::string, std::string> t :
       con.getConnections()) {
    try {
      std::string handlerId = std::get<1>(t);
      std::string pluginId = std::get<2>(t);
      Connection *connection = Connection::factory(handlerId, pluginId);
      connection->connect();
    } catch (std::exception &ex) {
      Logger::error(ex.what());
    }
  }
}

void Controller::startThreads() {
  for (HyphaHandler *handler : HandlerLoader::instance()->getInstances()) {
    Logger::info("start thread (h): " + handler->getId());
    handler->start();
  }
  for (HyphaPlugin *plugin : PluginLoader::instance()->getInstances()) {
    Logger::info("start thread (p): " + plugin->getId());
    plugin->setCallMessageFunction(Connection::communicate);
    plugin->setup();
  }
  for (HyphaPlugin *plugin : PluginLoader::instance()->getInstances()) {
    plugin->start();
  }
}
