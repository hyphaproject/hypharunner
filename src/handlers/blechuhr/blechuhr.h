// Copyright (c) 2015-2016 Hypha

#ifndef BLECHUHR_H
#define BLECHUHR_H

#include <string>
#include <hypha/handler/hyphahandler.h>

namespace hypha {
namespace handler {
namespace blechuhr {
class BlechUhr : public HyphaHandler {
 public:
  explicit BlechUhr();
  ~BlechUhr();
  static BlechUhr *instance();
  void doWork();
  const std::string name() { return "blechuhr"; }
  const std::string getTitle() { return "Blechuhr"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Handler like a time recorder."; }

  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string config);
  std::string getConfig();

  void parse(std::string message);
  void storeDevice(std::string device, std::string type);
  void giveFeedback(std::string device);
  void giveFeedback(std::string username, std::string device);
  int countDeviceToday(std::string device);

  HyphaHandler *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);
};
}
}
}

#endif  // BLECHUHR_H
