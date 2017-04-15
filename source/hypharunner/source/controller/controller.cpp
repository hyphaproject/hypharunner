// Copyright (c) 2015-2016 Hypha

#include "hypharunner/controller/controller.h"
#include "hypharunner/controller/connection.h"

#include <mutex>

#include <hypha/controller/connection.h>
#include <hypha/core/database/database.h>
#include <hypha/plugin/hyphasender.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginutil.h>
#include <hypha/utils/logger.h>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>

using namespace hypha::utils;
using namespace hypha::plugin;
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

void Controller::loadPlugins() {
  PluginLoader::instance()->loadLocalInstances();
}

void Controller::createConnections() {
  hypha::controller::Connection con(Database::instance());
  for (std::tuple<std::string, std::string, std::string> t :
       con.getConnections()) {
    try {
      std::string senderId = std::get<1>(t);
      std::string receiverId = std::get<2>(t);
      Connection *connection = Connection::factory(senderId, receiverId);
      connection->connect();
    } catch (std::exception &ex) {
      Logger::error(ex.what());
    }
  }
}

void Controller::startThreads() {
  for (HyphaBasePlugin *plugin : PluginLoader::instance()->getInstances()) {
    Logger::info("start thread: " + plugin->getId());
    if (PluginUtil::isSender(plugin))
      ((HyphaSender *)plugin)->setCallMessageFunction(Connection::communicate);
    plugin->setup();
  }
  for (HyphaBasePlugin *plugin : PluginLoader::instance()->getInstances()) {
    plugin->start();
  }
}
