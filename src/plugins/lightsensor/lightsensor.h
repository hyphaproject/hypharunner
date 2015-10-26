#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H
#include <hypha/plugin/hyphaplugin.h>
#include <mutex>
namespace hypha {
namespace plugin {
namespace lightsensor {
class LightSensor : public HyphaPlugin {
  public:
    void doWork();
    void setup();
    std::string name() {
        return "lightsensor";
    }
    std::string getTitle() {
        return "LightSensor";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to read light sensor";
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
    bool light = false;
};
}
}
}
#endif // LIGHTSENSOR_H
