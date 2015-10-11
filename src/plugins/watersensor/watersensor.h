#ifndef WATERSENSOR_H
#define WATERSENSOR_H
#include <mutex>
#include <hypha/plugin/hyphaplugin.h>
namespace hypha {
namespace plugin {
namespace watersensor {
class WaterSensor : public HyphaPlugin {
  public:
    void doWork();
    void setup();
    std::string name() {
        return "watersensor";
    }
    std::string getTitle() {
        return "WaterSensor";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to read water sensor";
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
    bool water = false;
    int PIN = 6;

};
}
}
}
#endif // WATERSENSOR_H
