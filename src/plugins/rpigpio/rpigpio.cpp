
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDebug>
#include <Poco/ClassLibrary.h>
#include <hypha/plugin/hyphaplugin.h>
#include "rpigpio.h"

using namespace hypha::plugin;
using namespace hypha::plugin::rpigpio;

void RpiGpio::doWork() {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void RpiGpio::setup() {
}

std::string RpiGpio::communicate(std::string message) {
    return getStatusMessage();
}

void RpiGpio::loadConfig(std::string json) {

}

std::string RpiGpio::getConfig() {
    return "{}";
}

hypha::plugin::HyphaPlugin *RpiGpio::getInstance(std::string id) {
    RpiGpio *instance = new RpiGpio();
    instance->setId(id);
    return instance;
}

void RpiGpio::receiveMessage(std::string message) {
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("python", QStringList() << "../plugins/rpigpio.py" << QString::fromStdString(message));
    process.waitForFinished();
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(RpiGpio)
POCO_END_MANIFEST
