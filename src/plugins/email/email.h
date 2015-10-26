#ifndef EMAIL_H
#define EMAIL_H
#include <hypha/plugin/hyphaplugin.h>

namespace hypha {
namespace plugin {
namespace email {
class EMail : public HyphaPlugin {
  public:
    void doWork();
    void setup();
    std::string communicate(std::string message);
    std::string name() {
        return "email";
    }
    std::string getTitle() {
        return "EMail";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to send emails.";
    }
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPlugin *getInstance(std::string id);

    void receiveMessage(std::string message);
    void sendMail(std::string content);

  private:
    std::string host;
    int port;
    std::string user;
    std::string password;
    std::string recipient;

};
}
}
}
#endif // EMAIL_H
