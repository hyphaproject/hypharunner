// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/plugin/hyphabaseplugin.h>

#include "hypharunner/controller/connection.h"

class NetworkConnection : public Connection {
 public:
  NetworkConnection(std::string senderId, std::string receiverId);
  virtual bool connect();
  virtual bool disconnect();
  void receiveMessage(std::string message);
  static std::string communicate(std::string id, std::string message);

 protected:
  hypha::plugin::HyphaBasePlugin *sender;
  hypha::plugin::HyphaBasePlugin *receiver;
  std::string receiverId;
  std::string senderId;
  std::string host;
  std::string id;
};
