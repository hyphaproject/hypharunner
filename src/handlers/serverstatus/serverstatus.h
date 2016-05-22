// Copyright (c) 2015-2016 Hypha

#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H

#include <string>
#include <hypha/handler/hyphahandler.h>

namespace hypha {
namespace handler {
namespace serverstatus {
class ServerStatus : public HyphaHandler {
 public:
  explicit ServerStatus();
  ~ServerStatus();
  static ServerStatus *instance();
  void doWork();
  const std::string name() { return "serverstatus"; }
  const std::string getTitle() { return "Server Status"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Handler to send server status as email";
  }

  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string config);
  std::string getConfig();

  void parse(std::string message);

  HyphaHandler *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

  void sendEMail();
};
}
}
}

#endif  // SERVERSTATUS_H
