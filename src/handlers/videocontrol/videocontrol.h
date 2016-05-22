// Copyright (c) 2015-2016 Hypha

#ifndef VIDEOCONTROL_H
#define VIDEOCONTROL_H

#include <string>
#include <mutex>
#include <thread>
#include <hypha/handler/hyphahandler.h>

namespace hypha {
namespace handler {
namespace videocontrol {
class VideoControl : public HyphaHandler {
 public:
  explicit VideoControl();
  ~VideoControl();
  static VideoControl *instance();
  void doWork();
  const std::string name() { return "videocontrol"; }
  const std::string getTitle() { return "VideoControl"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() { return "Handler for Video Control."; }
  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string config);
  std::string getConfig();

  void parse(std::string message);

  HyphaHandler *getInstance(std::string id);

  void receiveMessage(std::string message);
  std::string communicate(std::string message);

  void startVideoCapture();
  void stopVideoCapture();

 protected:
  std::string saveDir = "";
  int timer = 0;
  std::mutex timer_mutex;
  std::thread *startThread = 0;
};
}
}
}

#endif  // VIDEOCONTROL_H
