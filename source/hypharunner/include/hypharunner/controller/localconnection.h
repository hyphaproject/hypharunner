#ifndef LOCALCONNECTION_H
#define LOCALCONNECTION_H

#include <hypha/handler/hyphahandler.h>
#include <hypha/plugin/hyphaplugin.h>
#include <thread>

#include "hypharunner/controller/connection.h"

class LocalConnection : public Connection {
 public:
  LocalConnection(std::string handlerId, std::string pluginId);
  virtual bool connect();
  virtual bool disconnect();

  void handlerMessage(std::string message);
  void pluginMessage(std::string message);

  static std::string communicate(std::string id, std::string message);

 protected:
  hypha::handler::HyphaHandler *handler = 0;
  hypha::plugin::HyphaPlugin *plugin = 0;
  std::thread *handlerThread = 0;
  std::thread *pluginThread = 0;
};

#endif  // LOCALCONNECTION_H
