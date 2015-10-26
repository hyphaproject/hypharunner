#ifndef EXPLORENFC_H
#define EXPLORENFC_H
#include <hypha/plugin/hyphaplugin.h>
namespace hypha {
namespace plugin {
namespace explorenfc {
class ExploreNFC : public HyphaPlugin {
  public:
    void doWork();
    void setup();
    std::string communicate(std::string message);
    std::string name() {
        return "explorenfc";
    }
    std::string getTitle() {
        return "ExploreNFC";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to detect rfid cards.";
    }
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPlugin *getInstance(std::string id);

    void receiveMessage(std::string message);
  private:
};
}
}
}
#endif // EXPLORENFC_H
