#ifndef FINGERPRINTZFM_H
#define FINGERPRINTZFM_H
#include <iostream>
#include "AdafruitZFM/ZFMComm.h"
#include <hypha/plugin/hyphaplugin.h>
namespace hypha {
namespace plugin {
namespace fingerprintzfm {
class FingerPrintZFM : public HyphaPlugin {
 public:
  enum State {IDLE, SCANNING, PROGRAMMING};
  void doWork();
  void setup();
  std::string communicate(std::string message);
  std::string name() {
    return "fingerprintzfm";
  }
  std::string getTitle() {
    return "FingerprintZFM";
  }
  std::string getVersion() {
    return "0.1";
  }
  std::string getDescription() {
    return "Plugin to detect fingerprint with adafruit zfm.";
  }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaPlugin *getInstance(std::string id);

  void receiveMessage(std::string message);

  std::string getUsername(std::string fingerprintid);
  void createDatabase();
  void storeFingerprint(std::string fingerprintid);

  void clearFingerprints();
  void programming();
  void scanning();

 private:
  std::string usbPort;
  ZFMComm fp;
  State state;
  int storecount;
};
}
}
}
#endif // FINGERPRINTZFM_H
