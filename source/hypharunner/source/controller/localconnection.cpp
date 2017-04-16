// Copyright (c) 2015-2017 Hypha

#include "hypharunner/controller/localconnection.h"

#include <functional>
#include <memory>

#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>
#include <boost/shared_ptr.hpp>

using namespace hypha::plugin;

LocalConnection::LocalConnection(std::string senderId, std::string receiverId) {
  this->sender = PluginLoader::instance()->getPluginInstance(senderId);
  this->receiver = PluginLoader::instance()->getPluginInstance(receiverId);
}

bool LocalConnection::connect() {
  if (sender && receiver) {
    ((HyphaSender *)sender)
        ->connect(boost::bind(&LocalConnection::senderMessage, this, _1));
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
    senderThread = new std::thread([this, message] {
      ((HyphaReceiver *)this->receiver)->receiveMessage(message);
    });
  } catch (std::exception &e) {
    hypha::utils::Logger::error(e.what());
  } catch (...) {
    hypha::utils::Logger::error("Error in " + receiver->getId() +
                                " receiveMessage part.");
  }
}

std::string LocalConnection::communicate(std::string id, std::string message) {
  HyphaBasePlugin *plugin = PluginLoader::instance()->getPluginInstance(id);
  if (plugin) {
    return plugin->communicate(message);
  }
  return "";
}
