#ifndef SERVERSTATUS_H
#define SERVERSTATUS_H

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
  std::string name() {
    return "serverstatus";
  }
  std::string getTitle() {
    return "Server Status";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Handler to send server status as email";
  }
  void parse(std::string message);
  void loadConfig(std::string config);
  std::string getConfig();
  HyphaHandler *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

  void sendEMail();

 protected:

};
}
}
}

#endif // SERVERSTATUS_H
