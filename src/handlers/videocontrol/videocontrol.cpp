#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <thread>
#include <chrono>
#include <Poco/ClassLibrary.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/utils/logger.h>
#include "videocontrol.h"

using namespace hypha::database;
using namespace hypha::handler;
using namespace hypha::handler::videocontrol;
using namespace hypha::plugin;

VideoControl::VideoControl() {
}

VideoControl::~VideoControl() {

}

void VideoControl::doWork() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    timer_mutex.lock();
    timer ++;
    if (timer == 0) {
        stopVideoCapture();
    }
    timer_mutex.unlock();
}


void VideoControl::parse(std::string message) {
}

void VideoControl::loadConfig(std::string config) {
    boost::property_tree::ptree ptconfig;
    std::stringstream ssconfig(config);
    boost::property_tree::read_json(ssconfig, ptconfig);

    if (ptconfig.get_optional<std::string>("savedir")) {
        saveDir = ptconfig.get<std::string>("savedir");
    }
}

std::string VideoControl::getConfig() {
    return "{\"savedir\":\"" + saveDir + "\"}";
}

HyphaHandler *VideoControl::getInstance(std::string id) {
    VideoControl *instance = new VideoControl();
    instance->setId(id);
    return instance;
}

void VideoControl::receiveMessage(std::string message) {
    boost::property_tree::ptree ptjson;
    std::stringstream ssjson(message);
    boost::property_tree::read_json(ssjson, ptjson);

    if (ptjson.get_optional<bool>("movement") && ptjson.get_optional<bool>("movement") == true) {
        timer_mutex.lock();
        if (timer > 0) {
            if (startThread) {
                if (startThread->joinable())
                    startThread->join();
                delete startThread;
            }
            startThread = new std::thread( [this] { startVideoCapture(); });
        }
        timer = -10;
        timer_mutex.unlock();
    }
}

std::string VideoControl::communicate(std::string message) {
    return "";
}

void VideoControl::startVideoCapture() {
    sendMessage("{\"videocapture\":true, \"savedir\":\"" + saveDir + "\"}");
}

void VideoControl::stopVideoCapture() {
    sendMessage("{\"videocapture\":false}");
}

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(VideoControl)
POCO_END_MANIFEST
