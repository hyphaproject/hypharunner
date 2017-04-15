// Copyright (c) 2015-2016 Hypha

#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>

#include <boost/shared_ptr.hpp>
#include <functional>
#include <memory>

#include "hypharunner/controller/localconnection.h"

using namespace hypha::plugin;
using namespace hypha::handler;

LocalConnection::LocalConnection(std::string senderId, std::string receiverId) {
  this->sender = PluginLoader::instance()->getPluginInstance(senderId);
  this->receiver = PluginLoader::instance()->getPluginInstance(receiverId);
}

bool LocalConnection::connect() {
  if (sender && receiver) {
    ((HyphaSender*)sender)->connect(boost::bind(&LocalConnection::senderMessage, this, _1));
    return true;
  } else {
    return false;
  }
}

bool LocalConnection::disconnect() {
  // not implemented yet
  return false;
}

void LocalConnection::senderMessage(std::string message) {
  try {
    if (senderThread) {
      if (senderThread->joinable()) senderThread->join();
      delete senderThread;
    }
    senderThread = new std::thread(
        [this, message] { ((HyphaReceiver*)this->receiver)->receiveMessage(message); });
  } catch (std::exception &e) {
    hypha::utils::Logger::error(e.what());
  } catch (...) {
    hypha::utils::Logger::error("Error in " + receiver->getId() +
                                " receiveMessage part.");
  }
}

std::string LocalConnection::communicate(std::string id, std::string message) {
  HyphaHandler *handler = HandlerLoader::instance()->getHandlerInstance(id);
  if (handler) {
    return handler->communicate(message);
  }
  HyphaBasePlugin *plugin = PluginLoader::instance()->getPluginInstance(id);
  if (plugin) {
    return plugin->communicate(message);
  }
  return "";
}
