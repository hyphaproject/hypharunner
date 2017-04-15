// Copyright (c) 2015-2017 Hypha

#include "hypharunner/controller/connection.h"
#include "hypharunner/controller/localconnection.h"
#include "hypharunner/controller/networkconnection.h"

#include <functional>
#include <memory>

#include <Poco/Net/DNS.h>
#include <boost/shared_ptr.hpp>
#include <hypha/core/settings/handlersettings.h>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>

using namespace hypha::plugin;
using namespace hypha::handler;
using namespace hypha::settings;

Connection *Connection::factory(std::string senderId, std::string receiverId) {
  if ((PluginSettings::instance()->getHost(receiverId) ==
           Poco::Net::DNS::hostName() ||
       PluginSettings::instance()->getHost(receiverId) == "localhost") &&
      (HandlerSettings::instance()->getHost(senderId) ==
           Poco::Net::DNS::hostName() ||
       HandlerSettings::instance()->getHost(senderId) == "localhost")) {
    return new LocalConnection(senderId, receiverId);
  } else {
    return new NetworkConnection(senderId, receiverId);
  }
}

std::string Connection::communicate(std::string id, std::string message) {
  HyphaBasePlugin *plugin = PluginLoader::instance()->getPluginInstance(id);
  if (plugin) {
    if (PluginSettings::instance()->getHost(id) == Poco::Net::DNS::hostName() ||
        PluginSettings::instance()->getHost(id) == "localhost") {
      return LocalConnection::communicate(id, message);
    } else {
      return NetworkConnection::communicate(id, message);
    }
  }
  return "";
}

Connection::~Connection() {}

bool Connection::connect() { return false; }

bool Connection::disconnect() { return false; }
