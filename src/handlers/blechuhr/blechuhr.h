#ifndef BLECHUHR_H
#define BLECHUHR_H

#include <hypha/handler/hyphahandler.h>

namespace hypha {
namespace handler {
namespace blechuhr {
class BlechUhr : public HyphaHandler {
 public:
  explicit BlechUhr();
  ~BlechUhr();
  static BlechUhr *instance();
  void doWork();
  std::string name() {
    return "blechuhr";
  }
  std::string getTitle() {
    return "Blechuhr";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Handler like a time recorder.";
  }
  void parse(std::string message);
  void storeDevice(std::string device, std::string type);
  void giveFeedback(std::string device);
  void giveFeedback(std::string username, std::string device);
  int countDeviceToday(std::string device);
  void loadConfig(std::string config);
  std::string getConfig();
  HyphaHandler *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

 private:


};
}
}
}

#endif // BLECHUHR_H
