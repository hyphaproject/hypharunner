#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <hypha/handler/hyphahandler.h>
#include <hypha/plugin/hyphaplugin.h>
#include "hypharunner/controller/connection.h"

class NetworkConnection : public Connection {
 public:
  NetworkConnection(std::string handlerId, std::string pluginId);
  virtual bool connect();
  virtual bool disconnect();
  void receiveMessage(std::string message);
  static std::string communicate(std::string id, std::string message);

 protected:
  hypha::handler::HyphaHandler *handler;
  hypha::plugin::HyphaPlugin *plugin;
  std::string pluginId;
  std::string handlerId;
  std::string host;
  std::string id;
};

#endif  // NETWORKCONNECTION_H
