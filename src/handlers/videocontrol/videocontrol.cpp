#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <thread>
#include <chrono>
#include <QtCore/QDebug>
#include <QtCore/QDateTime>
#include <Poco/ClassLibrary.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
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
    if(timer == 0) {
        stopVideoCapture();
    }
    timer_mutex.unlock();
}


void VideoControl::parse(std::string message) {
}

void VideoControl::loadConfig(std::string config) {
    QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(config).toUtf8());
    QJsonObject object = document.object();
    if(object.contains("savedir")) {
        saveDir = object.value("savedir").toString().toStdString();
    }
}

std::string VideoControl::getConfig() {
    return "{\"savedir\":\""+saveDir+"\"}";
}

HyphaHandler *VideoControl::getInstance(std::string id) {
    VideoControl *instance = new VideoControl();
    instance->setId(id);
    return instance;
}

void VideoControl::receiveMessage(std::string message) {
    QJsonDocument document = QJsonDocument::fromJson(message.c_str());
    QJsonObject object = document.object();
    if(object.contains("movement") && object.value("movement").toBool() == true) {
        timer_mutex.lock();
        if(timer > 0) {
            if(startThread){
                if(startThread->joinable())
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
