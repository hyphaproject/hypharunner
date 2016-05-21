#ifndef WIFI_H
#define WIFI_H
#include <hypha/plugin/hyphaplugin.h>
namespace hypha {
namespace plugin {
namespace wifi {
class Wifi : public HyphaPlugin {
 public:
  void doWork();
  void setup();
  const std::string name() { return "wifi"; }
  const std::string getTitle() { return "Wifi"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Plugin to scan for mac adresses in the network.";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPlugin *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

 private:
};
}
}
}
#endif  // WIFI_H
