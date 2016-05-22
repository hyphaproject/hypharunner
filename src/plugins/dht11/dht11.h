// Copyright (c) 2015-2016 Hypha

#ifndef DHT11_H
#define DHT11_H

#include <string>
#include <mutex>
#include <hypha/plugin/hyphaplugin.h>

namespace hypha {
namespace plugin {
namespace dht11 {

class Dht11 : public HyphaPlugin {
 public:
  void doWork();
  void setup();
  std::string communicate(std::string message);
  const std::string name() { return "dht11"; }
  const std::string getTitle() { return "Dht11"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Plugin to read temperature and humidity sensor data";
  }
  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string json);
  std::string getConfig();
  std::string getStatusMessage();

  void measure();
  HyphaPlugin *getInstance(std::string id);

  void receiveMessage(std::string message);

 protected:
  std::mutex measure_mutex;
  int dht11_val[5] = {0, 0, 0, 0, 0};
  bool alarm = false;
  int maxtemp = 0;
  int mintemp = 0;
  float temperature = -1;
  float humidity = -1;
};
}
}
}
#endif  // DHT11_H
