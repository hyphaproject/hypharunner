// Copyright (c) 2015-2016 Hypha

#ifndef DOOROPENER_H
#define DOOROPENER_H

#include <string>
#include <hypha/handler/hyphahandler.h>

namespace hypha {
namespace handler {
namespace dooropener {
class DoorOpener : public HyphaHandler {
 public:
  explicit DoorOpener();
  ~DoorOpener();
  static DoorOpener *instance();
  void doWork();
  const std::string name() { return "dooropener"; }
  const std::string getTitle() { return "DoorOpener"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Handler to open doors."; }

  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string config);
  std::string getConfig();

  void parse(std::string message);
  void giveFeedback(std::string username);

  HyphaHandler *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

  void openDoor(std::string username);
  void closeDoor();

  bool accessAllowed(std::string user);

 protected:
  std::string mastercard;
  bool useFingerprint = false;
  bool email = false;
};
}
}
}

#endif  // DOOROPENER_H
