#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <Poco/ClassLibrary.h>
#include <hypha/plugin/eitplugin.h>
#include <hypha/utils/logger.h>
#include "lightsensor.h"

#define PIN 5

using namespace hypha::utils;
using namespace hypha::plugin;
using namespace hypha::plugin::lightsensor;

void LightSensor::doWork() {
    if(alarm) {
        measure();
        if(light) {
            QJsonObject object;
            object["alarm"] = true;
            object["id"] = QString::fromStdString(this->id);
            object["type"] = QString::fromStdString(name());
            object["light"] = light;
            object["value"] = light;
            QJsonDocument document(object);
            sendMessage(QString(document.toJson()).toStdString());
            std::this_thread::sleep_for(std::chrono::seconds(20));
        } else {
            QJsonObject object;
            object["alarm"] = false;
            object["id"] = QString::fromStdString(this->id);
            object["type"] = QString::fromStdString(name());
            object["light"] = light;
            object["value"] = light;
            QJsonDocument document(object);
            sendMessage(QString(document.toJson()).toStdString());
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void LightSensor::setup() {
    wiringPiSetup();
}

std::string LightSensor::communicate(std::string message) {
    return getStatusMessage();
}

std::string LightSensor::getStatusMessage() {
    measure();
    return light?"Light":"Dark";
}

void LightSensor::loadConfig(std::string json) {
    QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
    QJsonObject object = document.object();
    if(object.contains("alarm")) {
        alarm = object.value("alarm").toBool();
    }
}

std::string LightSensor::getConfig() {
    return "{}";
}

HyphaPlugin *LightSensor::getInstance(std::string id) {
    LightSensor *instance = new LightSensor();
    instance->setId(id);
    return instance;
}

void LightSensor::receiveMessage(std::string message) {
}

void LightSensor::measure() {
    measure_mutex.lock();
    this->light = (digitalRead(PIN)==HIGH);
    measure_mutex.unlock();
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(LightSensor)
POCO_END_MANIFEST
