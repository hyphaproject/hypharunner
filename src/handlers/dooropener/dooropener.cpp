#include <QtCore/QMutex>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <thread>
#include <chrono>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <QtSql/QSqlError>
#include <Poco/ClassLibrary.h>
#include <Poco/Data/Statement.h>
#include <Poco/Data/RecordSet.h>
#include <hypha/database/database.h>
#include <hypha/database/userdatabase.h>
#include <hypha/utils/logger.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/plugin/pluginloader.h>
#include "dooropener.h"

using namespace hypha::utils;
using namespace hypha::database;
using namespace hypha::settings;
using namespace hypha::handler;
using namespace hypha::handler::dooropener;
using namespace hypha::plugin;

DoorOpener::DoorOpener() {
  Poco::Data::Statement statement = Database::instance()->getStatement();
  statement << "CREATE TABLE IF NOT EXISTS dooropener_user ("
            "id varchar(32) NOT NULL,"
            "user varchar(128) NOT NULL,"
            "atworktime bool NOT NULL DEFAULT 0,"
            "PRIMARY KEY (id,user)"
            ") DEFAULT CHARSET=utf8;";
  statement.execute();
}

DoorOpener::~DoorOpener() {

}

void DoorOpener::doWork() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
}


void DoorOpener::parse(std::string message) {
  QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(message).toUtf8());
  QJsonObject object = document.object();
  if (object.contains("devices")) {
    foreach(QVariant device, object.value("devices").toArray().toVariantList()) {
      if (!device.toString().isEmpty()) {
        if (device.toString().toStdString() == mastercard) {
          sendMessage("{\"state\":\"PROGRAMMING\"}");
        } else {
          std::string username = UserDatabase::instance()->getOwnerOfDevice(device.toString().toStdString());
          if (useFingerprint) {
            giveFeedback(username);
          } else {
            if (accessAllowed(username)) {
              openDoor(username);
            } else {
              sendMessage("{\"say\":\"Access denied at this time.\"}");
            }
          }
        }
      }
    }
  } else if (object.contains("authuser")) {
    if (accessAllowed(object.value("authuser").toString().toStdString())) {
      openDoor(object.value("authuser").toString().toStdString());
    } else {
      sendMessage("{\"say\":\"Access denied at this time.\"}");
    }
  }
}

void DoorOpener::giveFeedback(std::string username) {
  std::string fullname = UserDatabase::instance()->getFirstname(username) + " " + UserDatabase::instance()->getLastname(username);
  if (username.empty()) {
    sendMessage("{\"red\":true, \"door\":false}");
    sendMessage("{\"say\":\"Zugang verweigert.\"}");
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    sendMessage("{\"red\":false, \"door\":false}");
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    sendMessage("{\"red\":true, \"door\":false}");
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    sendMessage("{\"red\":false,\"green\":false,\"yellow\":false, \"door\":false}");
  } else {
    sendMessage("{\"state\":\"SCANNING\"}");
    sendMessage("{\"say\":\"Guten Tag, " + fullname + ".\"}");
  }
}

void DoorOpener::loadConfig(std::string config) {
  QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(config).toUtf8());
  QJsonObject object = document.object();
  if (object.contains("mastercard")) {
    mastercard = object.value("mastercard").toString().toStdString();
  }
  if (object.contains("fingerprint")) {
    useFingerprint = object.value("fingerprint").toBool();
  }
  if (object.contains("email")) {
    email = object.value("email").toBool();
  }
}

std::string DoorOpener::getConfig() {
  return "{\"name\":\"dooropener\"}";
}

HyphaHandler *DoorOpener::getInstance(std::string id) {
  DoorOpener *dooropener = new DoorOpener();
  dooropener->setId(id);
  return dooropener;
}

void DoorOpener::receiveMessage(std::string message) {
  qDebug(message.c_str());
  if (QString::fromStdString(message).contains("\"say\":"))
    sendMessage(message);
  else
    parse(message);
}

std::string DoorOpener::communicate(std::string message) {
  return "";
}

void DoorOpener::openDoor(std::string username) {
  sendMessage("{\"say\":\"Tür geöffnet.\"}");
  sendMessage("{\"green\":true, \"beep\":600}");
  std::this_thread::sleep_for(std::chrono::milliseconds(400));
  sendMessage("{\"green\":false}");
  std::this_thread::sleep_for(std::chrono::milliseconds(400));
  sendMessage("{\"red\":false,\"green\":true,\"yellow\":false, \"door\":true}");
  sendMessage("{\"door\":true}");
  closeDoor();
  sendMessage("{\"mail\":\"" + username + " got access to door.\"}");
}

void DoorOpener::closeDoor() {
  std::this_thread::sleep_for(std::chrono::seconds(5));
  sendMessage("{\"green\":false, \"door\":false}");
  sendMessage("{\"say\":\"Tür geschlossen.\"}");
}

bool DoorOpener::accessAllowed(std::string user) {
  if (user.empty())
    return false;
  Poco::Data::Statement statement = Database::instance()->getStatement();
  std::string q("select atworktime from dooropener_user where id = '" + id + "' and user = '" + user + "';");
  statement << q;
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    if (rs[0].convert<bool>()) {
      q = "select type,start,end,starttime,endtime from iterativeaccount where username = '" + user + "';";
      statement << q;
      statement.execute();
      rs = Poco::Data::RecordSet(statement);
      more = rs.moveFirst();
      while ( more ) {
        QDateTime now = QDateTime::currentDateTime();
        std::string type = rs[0].convert<std::string>();
        QDate start = QDate::fromString(QString::fromStdString(rs[1].convert<std::string>()));
        QDate end = QDate::fromString(QString::fromStdString(rs[2].convert<std::string>()));
        QTime starttime = QTime::fromString(QString::fromStdString(rs[3].convert<std::string>()));
        QTime endtime = QTime::fromString(QString::fromStdString(rs[4].convert<std::string>()));
        Logger::warning(type);
        switch (now.date().dayOfWeek()) {
          case 1:
            if (type != "workingmon")
              return false;
            break;
          case 2:
            if (type != "workingtue")
              return false;
            break;
          case 3:
            if (type != "workingwed")
              return false;
            break;
          case 4:
            if (type != "workingthu")
              return false;
            break;
          case 5:
            if (type != "workingfri")
              return false;
            break;
          case 6:
            if (type != "workingsat")
              return false;
            break;
          case 7:
            if (type != "workingsun")
              return false;
            break;
          default:
            break;
        };
        if (start <= now.date() && end >= now.date()) {
          if (starttime <= now.time() && endtime >= now.time()) {
            return true;
          }
        }
        more = rs.moveNext();
      }
    } else {
      return true;
    }
    more = rs.moveNext();
  }
  return false;
}
POCO_BEGIN_MANIFEST(HyphaHandler)
POCO_EXPORT_CLASS(DoorOpener)
POCO_END_MANIFEST
