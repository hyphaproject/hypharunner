// Copyright (c) 2015-2016 Hypha

#ifndef FLAME_H
#define FLAME_H

#include <string>
#include <mutex>
#include <hypha/plugin/hyphaplugin.h>

namespace hypha {
namespace plugin {
namespace flame {
class Flame : public HyphaPlugin {
 public:
  void doWork();
  void setup();
  const std::string name() { return "flame"; }
  const std::string getTitle() { return "Flame"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Plugin to read flame sensor data";
  }
  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string json);
  std::string getConfig();
  std::string getStatusMessage();

  void measure();
  HyphaPlugin *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

 private:
  std::mutex measure_mutex;
  bool flame = false;
  bool alarm = false;
};
}
}
}
#endif  // FLAME_H
