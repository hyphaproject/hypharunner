// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/plugin/connection.h>
#include <hypha/plugin/hyphabaseplugin.h>

class NetworkConnection : public hypha::plugin::Connection {
 public:
  NetworkConnection(std::string senderId, std::string receiverId);
  virtual bool connect(std::shared_ptr<Connection> connection) override;
  virtual bool disconnect() override;
  virtual void sendMessage(std::string message) override;
  static std::string communicate(std::string id, std::string message);
  virtual ~NetworkConnection() {}

 protected:
  hypha::plugin::HyphaBasePlugin *sender;
  hypha::plugin::HyphaBasePlugin *receiver;
  std::string receiverId;
  std::string senderId;
  std::string host;
  std::string id;
};
