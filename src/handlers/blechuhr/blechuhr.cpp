#include <thread>
#include <chrono>

#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

#include <Poco/ClassLibrary.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/utils/logger.h>
#include "blechuhr.h"

using namespace hypha::utils;
using namespace hypha::database;
using namespace hypha::handler;
using namespace hypha::handler::blechuhr;
using namespace hypha::plugin;

BlechUhr::BlechUhr() {
}

BlechUhr::~BlechUhr() {

}

void BlechUhr::doWork() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    qDebug("blechuhr ...");
    sendMessage("{\"state\":\"SCANNING\"}");
}


void BlechUhr::parse(std::string message) {
    QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(message).toUtf8());
    QJsonObject object = document.object();
    if (object.contains("devices")) {
        foreach(QVariant device, object.value("devices").toArray().toVariantList()) {
            if (!device.toString().isEmpty()) {
                std::string type = object.value("devicetype").toString().toStdString();
                if (type == "rfid") {
                    storeDevice(device.toString().toStdString(), type);
                    giveFeedback(device.toString().toStdString());
                } else if (type == "wifi") {
                    storeDevice(device.toString().toStdString(), type);
                } else if (type == "fingerprint") {
                    storeDevice(device.toString().toStdString(), type);
                    giveFeedback(device.toString().toStdString());
                } else {
                    storeDevice(device.toString().toStdString(), "other");
                }
            }
        }
    } else if (object.contains("authuser")) {
        std::string device = "authuser" + object.value("authuser").toString().toStdString();
        storeDevice(device, "other");
        giveFeedback(object.value("authuser").toString().toStdString(), device);
    }
}

void BlechUhr::storeDevice(std::string device, std::string type) {
    Poco::Data::Statement statement = Database::instance()->getStatement();
    std::string time = QDateTime::currentDateTime().toUTC().toString("yyyy-MM-dd hh::mm").toStdString();
    statement << "insert into deviceonline(deviceid, time, type) values(?, ?, ?);",
              Poco::Data::Keywords::use(device),
              Poco::Data::Keywords::use(time),
              Poco::Data::Keywords::use(type);
    statement.execute();
}

void BlechUhr::giveFeedback(std::string device) {
    std::string username = UserDatabase::instance()->getOwnerOfDevice(device);
    giveFeedback(username, device);
}

void BlechUhr::giveFeedback(std::string username, std::string device) {
    std::string fullname = UserDatabase::instance()->getFirstname(username) + " " + UserDatabase::instance()->getLastname(username);
    // name unknown
    if (username.empty()) {
        sendMessage("{\"yellow\":true, \"door\":false}");
        sendMessage("{\"say\":\"Guten Tag, kenne ich Sie?\"}");
        sendMessage("{\"yellow\":false, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"yellow\":true, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"yellow\":false, \"door\":false}");
        sendMessage("{\"red\":false,\"green\":false,\"yellow\":false, \"door\":false}");
        Logger::info("[blechuhr] Unknown user: " + username + "(" + device + ")");
    } else if (countDeviceToday(device) % 2 == 0) { // goodbye
        sendMessage("{\"red\":true,\"beep\":200, \"door\":false}");
        sendMessage("{\"say\":\"Auf Wiedersehen " + fullname + ".\"}");
        sendMessage("{\"red\":false, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"red\":true, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"red\":false, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"red\":true, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"red\":false,\"green\":false,\"yellow\":false,\"beep\":200, \"door\":false}");
        Logger::info("[blechuhr] User checked out: " + username + "(" + device + ")");
    } else { // welcome
        sendMessage("{\"green\":true, \"beep\":600, \"door\":false}");
        sendMessage("{\"say\":\"Guten Tag, " + fullname + ".\"}");
        sendMessage("{\"green\":false, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"green\":true, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"green\":false, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"green\":true, \"door\":false}");
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        sendMessage("{\"green\":false,\"green\":false,\"yellow\":false, \"door\":false}");
        Logger::info("[blechuhr] User checked in: " + username + "(" + device + ")");
    }
}

int BlechUhr::countDeviceToday(std::string device) {
    int retValue = 0;
    Poco::Data::Statement statement = Database::instance()->getStatement();
    statement << "select count(id) from deviceonline where deviceid='" + device + "' and DATE(time) = '"
                 + QDateTime::currentDateTimeUtc().date().toString("yyyy-MM-dd").toStdString() + "'", Poco::Data::Keywords::into(retValue);
    statement.execute();
    return retValue;
}

void BlechUhr::loadConfig(std::string config) {

}

std::string BlechUhr::getConfig() {
    return "{\"name\":\"blechuhr\"}";
}

HyphaHandler *BlechUhr::getInstance(std::string id) {
    BlechUhr *blechuhr = new BlechUhr();
    blechuhr->setId(id);
    return blechuhr;
}

void BlechUhr::receiveMessage(std::string message) {
    parse(message);
}

std::string BlechUhr::communicate(std::string message) {
    return "";
}
POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(BlechUhr)
POCO_END_MANIFEST
