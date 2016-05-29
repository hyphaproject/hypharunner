#include <Poco/Net/DNS.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <memory>

#include <hypha/core/settings/handlersettings.h>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>

#include "hypharunner/controller/connection.h"
#include "hypharunner/controller/localconnection.h"
#include "hypharunner/controller/networkconnection.h"

using namespace hypha::plugin;
using namespace hypha::handler;
using namespace hypha::settings;

Connection *Connection::factory(std::string handlerId, std::string pluginId) {
  if ((PluginSettings::instance()->getHost(pluginId) ==
           Poco::Net::DNS::hostName() ||
       PluginSettings::instance()->getHost(pluginId) == "localhost") &&
      (HandlerSettings::instance()->getHost(handlerId) ==
           Poco::Net::DNS::hostName() ||
       HandlerSettings::instance()->getHost(handlerId) == "localhost")) {
    return new LocalConnection(handlerId, pluginId);
  } else {
    return new NetworkConnection(handlerId, pluginId);
  }
}

std::string Connection::communicate(std::string id, std::string message) {
  HyphaHandler *handler = HandlerLoader::instance()->getHandlerInstance(id);
  if (handler) {
    if (HandlerSettings::instance()->getHost(id) ==
            Poco::Net::DNS::hostName() ||
        HandlerSettings::instance()->getHost(id) == "localhost") {
      return LocalConnection::communicate(id, message);
    } else {
      return NetworkConnection::communicate(id, message);
    }
  }
  HyphaPlugin *plugin = PluginLoader::instance()->getPluginInstance(id);
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
