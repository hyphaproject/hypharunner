#ifndef ALARM_H
#define ALARM_H

#include <hypha/handler/hyphahandler.h>
#include <map>

namespace hypha {
namespace handler {
namespace alarm {
class Alarm : public HyphaHandler {
 public:
  explicit Alarm();
  ~Alarm();
  static Alarm *instance();
  void doWork();
  std::string name() {
    return "alarm";
  }
  std::string getTitle() {
    return "Alarm";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Handler for Alarm Control.";
  }
  void parse(std::string message);
  void loadConfig(std::string config);
  std::string getConfig();
  HyphaHandler *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

 protected:
  std::map<std::string, bool> alarm;

};
}
}
}

#endif // ALARM_H
