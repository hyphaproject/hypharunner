// Copyright (c) 2015-2017 Hypha

#include "hypharunner/controller/connectionfactory.h"
#include "hypharunner/controller/localconnection.h"
#include "hypharunner/controller/networkconnection.h"

#include <functional>
#include <memory>

#include <Poco/Net/DNS.h>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/plugin/pluginloader.h>
#include <boost/shared_ptr.hpp>

using namespace hypha::plugin;
using namespace hypha::settings;

std::shared_ptr<Connection> ConnectionFactory::factory(std::string senderId,
                                                       std::string receiverId) {
  if ((PluginSettings::instance()->getHost(receiverId) ==
           Poco::Net::DNS::hostName() ||
       PluginSettings::instance()->getHost(receiverId) == "localhost") &&
      (PluginSettings::instance()->getHost(senderId) ==
           Poco::Net::DNS::hostName() ||
       PluginSettings::instance()->getHost(senderId) == "localhost")) {
    return std::make_shared<LocalConnection>(senderId, receiverId);
  } else {
    return std::make_shared<NetworkConnection>(senderId, receiverId);
  }
}
