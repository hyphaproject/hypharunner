#ifndef ESPEAK_H
#define ESPEAK_H
#include <hypha/plugin/hyphaplugin.h>
namespace hypha {
namespace plugin {
namespace espeak {
class ESpeak : public HyphaPlugin {
  public:
    void doWork();
    void setup();
    std::string communicate(std::string message);
    std::string name() {
        return "espeak";
    }
    std::string getTitle() {
        return "ESpeak";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to speak text with espeak.";
    }
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPlugin *getInstance(std::string id);

    void receiveMessage(std::string message);


  private:
    std::string language;
};
}
}
}
#endif // ESPEAK_H
