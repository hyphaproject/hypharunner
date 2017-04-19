// Copyright (c) 2015-2017 Hypha

#include "hypharunner/controller/localconnection.h"

#include <functional>
#include <memory>

#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>

using namespace hypha::plugin;

LocalConnection::LocalConnection(std::string senderId, std::string receiverId)
    : Connection(senderId, receiverId) {
  this->sender = dynamic_cast<HyphaSender *>(
      PluginLoader::instance()->getPluginInstance(senderId));
  this->receiver = dynamic_cast<HyphaReceiver *>(
      PluginLoader::instance()->getPluginInstance(receiverId));
}

bool LocalConnection::connect(std::shared_ptr<Connection> connection) {
  if (sender && receiver) {
    sender->addListener(connection);
    sender->setCallMessageFunction(LocalConnection::communicate);
    return true;
  } else {
    return false;
  }
}

bool LocalConnection::disconnect() {
  // not implemented yet
  return false;
}

void LocalConnection::sendMessage(std::string message) {
  try {
    if (senderThread) {
      if (senderThread->joinable()) senderThread->join();
      delete senderThread;
    }
    senderThread = new std::thread([this, message] {
      try {
        receiver->receiveMessage(message);
      } catch (...) {
        hypha::utils::Logger::error("Error in " + receiverId +
                                    " receiveMessage part.");
      }
    });
  } catch (std::exception &e) {
    hypha::utils::Logger::error(e.what());
  } catch (...) {
    hypha::utils::Logger::error("Error in " + receiverId +
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
