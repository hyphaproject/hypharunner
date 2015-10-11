#ifndef RPIPIR_H
#define RPIPIR_H
#include <hypha/plugin/hyphaplugin.h>
#include <mutex>
namespace hypha {
namespace plugin {
namespace rpipir {
class RpiPir : public HyphaPlugin {
  public:
    void doWork();
    void setup();
    std::string name() {
        return "rpipir";
    }
    std::string getTitle() {
        return "RPI PIR";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to detect motion with a motion sensor";
    }
    void loadConfig(std::string json);
    std::string getConfig();
    std::string getStatusMessage();
    HyphaPlugin *getInstance(std::string id);

    void receiveMessage(std::string message);
    std::string communicate(std::string message);

    void measure();
    void sendMovement();
    bool getMovement();
  protected:
    std::mutex measure_mutex;
    bool alarm = false;
    bool log = false;
    std::mutex movement_mutex;
    bool movement = false;
    int PIN = 29;

};
}
}
}
#endif // RPIPIR_H
