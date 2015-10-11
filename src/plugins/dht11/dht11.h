#ifndef DHT11_H
#define DHT11_H
#include <mutex>
#include <hypha/plugin/eitplugin.h>

namespace hypha {
namespace plugin {
namespace dht11 {

class Dht11 : public HyphaPlugin {
  public:
    void doWork();
    void setup();
    std::string communicate(std::string message);
    std::string name() {
        return "dht11";
    }
    std::string getTitle() {
        return "Dht11";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to read temperature and humidity sensor data";
    }
    std::string getStatusMessage();
    void loadConfig(std::string json);
    std::string getConfig();
    void measure();
    HyphaPlugin *getInstance(std::string id);

    void receiveMessage(std::string message);

  protected:
    std::mutex measure_mutex;
    int dht11_val[5]= {0,0,0,0,0};
    bool alarm = false;
    int maxtemp = 0;
    int mintemp = 0;
    float temperature = -1;
    float humidity = -1;

};
}
}
}
#endif // DHT11_H
