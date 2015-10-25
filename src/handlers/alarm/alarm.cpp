#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <Poco/ClassLibrary.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/plugin/pluginloader.h>
#include "alarm.h"

using namespace hypha::handler;
using namespace hypha::handler::alarm;
using namespace hypha::plugin;
using namespace hypha::settings;
using namespace hypha::database;

Alarm::Alarm() {
}

Alarm::~Alarm() {

}

void Alarm::doWork() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Alarm::parse(std::string message) {
}

void Alarm::loadConfig(std::string config) {
}

std::string Alarm::getConfig() {
  return "{}";
}

HyphaHandler *Alarm::getInstance(std::string id) {
  Alarm *instance = new Alarm();
  instance->setId(id);
  return instance;
}

void Alarm::receiveMessage(std::string message) {
  boost::property_tree::ptree ptjson;
  std::stringstream ssjson(message);
  boost::property_tree::read_json(ssjson, ptjson);

  boost::property_tree::ptree sendobject;

  if (ptjson.get_optional<bool>("movement")) {
    std::string mail = "movement";
    sendobject.put("mail", mail);
  }

  if (ptjson.get_optional<bool>("alarm")) {
    std::string id = ptjson.get<std::string>("id");
    bool isAlarm = ptjson.get<bool>("alarm");
    if (alarm.find(id) == alarm.end()) {
      alarm[id] = isAlarm;
    } else if (alarm[id] != isAlarm) {
      alarm[id] = isAlarm;
      std::string value;
      if (ptjson.get_optional<bool>("value")) {
        value = ptjson.get<bool>("value") ? "true" : "false";
      } else if (ptjson.get_optional<double>("value")) {
        std::stringstream tostring;
        tostring << ptjson.get<double>("value");
        value = tostring.str();
      } else {
        value = ptjson.get<std::string>("value");
      }
      sendobject.put("mail", ptjson.get<std::string>("id") + "("
                     + ptjson.get<std::string>("type") + ") " + value);

      std::stringstream ssso;
      boost::property_tree::write_json(ssso, sendobject);
      sendMessage(ssso.str());
    }
  }
}

std::string Alarm::communicate(std::string message) {
  return "";
}

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(Alarm)
POCO_END_MANIFEST
