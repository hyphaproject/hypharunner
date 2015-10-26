#ifndef DOOROPENER_H
#define DOOROPENER_H

#include <hypha/handler/hyphahandler.h>

namespace hypha {
namespace handler {
namespace dooropener {
class DoorOpener : public HyphaHandler {
  public:
    explicit DoorOpener();
    ~DoorOpener();
    static DoorOpener *instance();
    void doWork();
    std::string name() {
        return "dooropener";
    }
    std::string getTitle() {
        return "DoorOpener";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Handler to open doors.";
    }

    void parse(std::string message);
    void giveFeedback(std::string username);
    void loadConfig(std::string config);
    std::string getConfig();
    HyphaHandler *getInstance(std::string id);

    void receiveMessage(std::string message);
    std::string communicate(std::string message);

    void openDoor(std::string username);
    void closeDoor();

    bool accessAllowed(std::string user);

  protected:
    std::string mastercard;
    bool useFingerprint = false;
    bool email = false;
};
}
}
}

#endif // DOOROPENER_H
