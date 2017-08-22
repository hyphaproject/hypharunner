// Copyright (c) 2015-2017 Hypha
#pragma once

#include <hypha/plugin/connection.h>
#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/hyphareceiver.h>
#include <hypha/plugin/hyphasender.h>
#include <hypha/utils/namesystem.h>

class NetworkConnection : public hypha::plugin::Connection {
 public:
  NetworkConnection(std::shared_ptr<hypha::utils::NameSystem> namesystem, std::string senderId, std::string receiverId);
  virtual bool connect(std::shared_ptr<Connection> connection) override;
  virtual bool disconnect() override;
  virtual void sendMessage(std::string message) override;
  static std::string communicate(std::string id, std::string message);
  virtual ~NetworkConnection() {}

 protected:
  hypha::plugin::HyphaSender *sender;
  hypha::plugin::HyphaReceiver *receiver;
  std::string receiverId;
  std::string senderId;
  std::string host;
  std::string id;
  std::shared_ptr<hypha::utils::NameSystem> namesystem;
};
