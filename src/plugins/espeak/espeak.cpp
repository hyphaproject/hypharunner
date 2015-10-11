
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <Poco/ClassLibrary.h>
#include <hypha/plugin/hyphaplugin.h>
#include "espeak.h"

using namespace hypha::plugin;
using namespace hypha::plugin::espeak;


void ESpeak::doWork() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void ESpeak::setup() {
    language = "de";
    receiveMessage("{\"say\":\"Starting.\"}");
}

std::string ESpeak::communicate(std::string message) {
    return "SUCCESS";
}

void ESpeak::loadConfig(std::string json) {

}

std::string ESpeak::getConfig() {
    return "{}";
}

HyphaPlugin *ESpeak::getInstance(std::string id) {
    ESpeak *instance = new ESpeak();
    instance->setId(id);
    return instance;
}

void ESpeak::receiveMessage(std::string message) {
    QJsonDocument document = QJsonDocument::fromJson(message.c_str());
    QJsonObject object = document.object();

    if(object.contains("language")) {
        language = object.value("language").toString().toStdString();
    }

    if(object.contains("say")) {
        std::string say = object.value("say").toString().toStdString();

        QProcess process;
        QStringList arguments;
        arguments << "-a 200";
        arguments << "-v"+QString::fromStdString(language)+"+f5";
        arguments << QString::fromStdString(say);
        if(process.execute("espeak", arguments) != 0) {
            sendMessage("FAILED");
        }
    }
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(ESpeak)
POCO_END_MANIFEST
