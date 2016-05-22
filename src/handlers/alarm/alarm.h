// Copyright (c) 2015-2016 Hypha

#ifndef ALARM_H
#define ALARM_H

#include <string>
#include <map>
#include <string>

#include <hypha/handler/hyphahandler.h>

namespace hypha {
namespace handler {
namespace alarm {
class Alarm : public HyphaHandler {
 public:
  explicit Alarm();
  ~Alarm();
  static Alarm *instance();
  void doWork();
  const std::string name() { return "alarm"; }
  const std::string getTitle() { return "Alarm"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Handler for Alarm Control."; }

  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string config);
  std::string getConfig();

  void parse(std::string message);
  HyphaHandler *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

 protected:
  std::map<std::string, bool> alarm;
};
}
}
}

#endif  // ALARM_H
