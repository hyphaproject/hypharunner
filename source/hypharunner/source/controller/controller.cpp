// Copyright (c) 2015-2017 Hypha

#include "hypharunner/controller/controller.h"
#include "hypharunner/controller/connectionfactory.h"
#include "hypharunner/controller/localconnection.h"
#include "hypharunner/controller/networkconnection.h"

#include <mutex>

#include <hypha/controller/connection.h>
#include <hypha/core/database/database.h>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/plugin/connection.h>
#include <hypha/plugin/hyphasender.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginutil.h>
#include <hypha/utils/logger.h>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>
#include <Poco/Net/DNS.h>

using namespace hypha::utils;
using namespace hypha::plugin;
using namespace hypha::database;

Controller *Controller::singleton = nullptr;

Controller::Controller() {
    namesystem = std::shared_ptr<hypha::utils::NameSystem>();
    namesystem->start();
}

Controller::~Controller() {
    namesystem->stop();
}

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
      std::shared_ptr<Connection> connection =
          ConnectionFactory::factory(namesystem, senderId, receiverId);
      connections.push_back(connection);
      connection->connect(connection);
    } catch (std::exception &ex) {
      Logger::error(ex.what());
    }
  }
}

void Controller::startThreads() {
  for (HyphaBasePlugin *plugin : PluginLoader::instance()->getInstances()) {
    Logger::info("start thread: " + plugin->getId());

    plugin->setup();
  }
  for (HyphaBasePlugin *plugin : PluginLoader::instance()->getInstances()) {
    plugin->start();
  }
}

std::string Controller::communicate(std::string id, std::string message) {
  HyphaBasePlugin *plugin = PluginLoader::instance()->getPluginInstance(id);
  if (plugin) {
    if (hypha::settings::PluginSettings::instance()->getHost(id) ==
            Poco::Net::DNS::hostName() ||
        hypha::settings::PluginSettings::instance()->getHost(id) ==
            "localhost") {
      return LocalConnection::communicate(id, message);
    } else {
      return NetworkConnection::communicate(id, message);
    }
  }
  return "";
}
