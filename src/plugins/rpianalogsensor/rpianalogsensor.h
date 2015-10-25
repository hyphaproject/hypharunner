#ifndef RPIANALOGSENSOR_H
#define RPIANALOGSENSOR_H
#include <mutex>
#include <hypha/plugin/hyphaplugin.h>
namespace hypha {
namespace plugin {
namespace rpianalogsensor {
class RpiAnalogSensor : public HyphaPlugin {
 public:
  void doWork();
  void setup();
  std::string name() {
    return "rpianalogsensor";
  }
  std::string getTitle() {
    return "RpiAnalogSensor";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Plugin to read analog sensor";
  }
  std::string getStatusMessage();
  void loadConfig(std::string json);
  std::string getConfig();
  void measure();
  HyphaPlugin *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

 private:
  std::mutex measure_mutex;
  bool alarm = false;
  int analog = -1;
  int PIN = 6;
  int min = 1;
  int max = 1023;
  int counter = 0;

};
}
}
}
#endif // RPIANALOGSENSOR_H
