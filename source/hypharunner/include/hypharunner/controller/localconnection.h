// Copyright (c) 2015-2016 Hypha
#pragma once

#include "hypharunner/controller/connection.h"

#include <thread>

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/hyphareceiver.h>
#include <hypha/plugin/hyphasender.h>

class LocalConnection : public Connection {
 public:
  LocalConnection(std::string senderId, std::string receiverId);
  virtual bool connect();
  virtual bool disconnect();

  void senderMessage(std::string message);

  static std::string communicate(std::string id, std::string message);

 protected:
  hypha::plugin::HyphaBasePlugin *sender = nullptr;
  hypha::plugin::HyphaBasePlugin *receiver = nullptr;
  std::thread *senderThread = nullptr;
  std::thread *receiverThread = nullptr;
};
