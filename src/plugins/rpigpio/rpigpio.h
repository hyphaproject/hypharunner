#ifndef RPIGPIO_H
#define RPIGPIO_H
#include <hypha/plugin/hyphaplugin.h>
namespace hypha {
namespace plugin {
namespace rpigpio {
class RpiGpio : public HyphaPlugin {
 public:
  void doWork();
  void setup();
  std::string name() {
    return "rpigpio";
  }
  std::string getTitle() {
    return "RPI GPIO";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Plugin to access gpio of the raspberry pi";
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
#endif // RPIGPIO_H
