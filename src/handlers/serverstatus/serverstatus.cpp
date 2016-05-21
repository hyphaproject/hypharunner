#include "serverstatus.h"
#include <Poco/ClassLibrary.h>
#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>
#include <QtCore/QDateTime>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QMutex>
#include <chrono>
#include <thread>

using namespace hypha::utils;
using namespace hypha::database;
using namespace hypha::handler;
using namespace hypha::handler::serverstatus;
using namespace hypha::plugin;

ServerStatus::ServerStatus() {}

ServerStatus::~ServerStatus() {}

void ServerStatus::doWork() {
  std::this_thread::sleep_for(std::chrono::seconds(10));
  sendEMail();
  std::this_thread::sleep_for(std::chrono::hours(23));
}

void ServerStatus::parse(std::string message) {
  QJsonDocument document =
      QJsonDocument::fromJson(QString::fromStdString(message).toUtf8());
  QJsonObject object = document.object();
}

void ServerStatus::loadConfig(std::string UNUSED(config)) {}

std::string ServerStatus::getConfig() { return "{}"; }

HyphaHandler *ServerStatus::getInstance(std::string id) {
  ServerStatus *instance = new ServerStatus();
  instance->setId(id);
  return instance;
}

void ServerStatus::receiveMessage(std::string UNUSED(message)) {}

std::string ServerStatus::communicate(std::string UNUSED(message)) {
  return "";
}

void ServerStatus::sendEMail() {
  std::string message = "Server Status\n\n";
  for (std::string pluginId :
       HandlerLoader::instance()->getConnectedPlugins(id)) {
    HyphaPlugin *p = PluginLoader::instance()->getPluginInstance(pluginId);
    if (p) {
      message +=
          "Component of Type " + p->name() + " with ID " + p->getId() + ":\n";
      message += "Description: " + p->getDescription() + "\n";
      message += callMessage(pluginId, "");
      message += "\n- - - - - - - - - - - -\n";
    }
  }
  Logger::info("ServerStatus message:");
  Logger::info(message);
  QJsonObject sendobject;
  sendobject["mail"] = QString::fromStdString(message);
  QJsonDocument senddocument(sendobject);
  sendMessage(QString(senddocument.toJson()).toStdString());
}
POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(ServerStatus)
POCO_END_MANIFEST
