// Copyright (c) 2015-2016 Hypha
#pragma once

#include <thread>

#include <hypha/plugin/connection.h>
#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/hyphareceiver.h>
#include <hypha/plugin/hyphasender.h>

class LocalConnection : public hypha::plugin::Connection {
 public:
  LocalConnection(std::string senderId, std::string receiverId);
  bool connect(std::shared_ptr<Connection> connection) override;
  bool disconnect() override;

  virtual void sendMessage(std::string message) override;

  static std::string communicate(std::string id, std::string message);

 protected:
  hypha::plugin::HyphaSender *sender = nullptr;
  hypha::plugin::HyphaReceiver *receiver = nullptr;
  std::thread *senderThread = nullptr;
  std::thread *receiverThread = nullptr;
};
