#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QDateTime>
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
    QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(message).toUtf8());
    QJsonObject object = document.object();
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
    QJsonDocument document = QJsonDocument::fromJson(message.c_str());
    QJsonObject object = document.object();
    QJsonObject sendobject;
    if(object.contains("movement")) {
        sendobject["mail"] = "movement";
    }

    if(object.contains("alarm")) {
        std::string id = object["id"].toString().toStdString();
        bool isAlarm = object.value("alarm").toBool();
        if(alarm.find(id) == alarm.end()) {
            alarm[id] = isAlarm;
        } else if(alarm[id] != isAlarm) {
            alarm[id] = isAlarm;
            std::string value;
            if(object["value"].isBool()) {
                value = object["value"].toBool()?"true":"false";
            } else if(object["value"].isDouble()) {
                std::stringstream tostring;
                tostring << object["value"].toDouble();
                value = tostring.str();
            } else {
                value = object["value"].toString().toStdString();
            }
            sendobject["mail"] = object["id"].toString()+"("+object["type"].toString()+") " + QString::fromStdString(value);
            QJsonDocument senddocument(sendobject);
            sendMessage(QString(senddocument.toJson()).toStdString());
        }
    }
}

std::string Alarm::communicate(std::string message) {
    return "";
}

POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(Alarm)
POCO_END_MANIFEST
