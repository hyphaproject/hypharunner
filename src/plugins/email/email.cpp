
#include <QtCore/QProcess>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include <Poco/ClassLibrary.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/utils/logger.h>
#include "email.h"

using namespace hypha::utils;
using namespace hypha::plugin;
using namespace hypha::plugin::email;

void EMail::doWork() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void EMail::setup() {
}

std::string EMail::communicate(std::string message) {
    return "NOTSUPPORTED";
}

void EMail::loadConfig(std::string json) {
    QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
    QJsonObject object = document.object();
    if(object.contains("user")) {
        user = object.value("user").toString().toStdString();
    }
    if(object.contains("host")) {
        host = object.value("host").toString().toStdString();
    }
    if(object.contains("port")) {
        port = object.value("port").toInt();
    }
    if(object.contains("password")) {
        password = object.value("password").toString().toStdString();
    }
    if(object.contains("recipient")) {
        recipient = object.value("recipient").toString().toStdString();
    }
}

std::string EMail::getConfig() {
    return "{}";
}

HyphaPlugin *EMail::getInstance(std::string id) {
    EMail *instance = new EMail();
    instance->setId(id);
    return instance;
}

void EMail::receiveMessage(std::string message) {
    QJsonDocument document = QJsonDocument::fromJson(message.c_str());
    QJsonObject object = document.object();

    if(object.contains("mail")) {
        std::string message = object.value("mail").toString().toStdString();
        sendMail(message);
    }
}

void EMail::sendMail(std::string content) {
    Poco::Net::MailMessage message;
    message.setSender(this->user);
    message.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, this->recipient));
    message.setSubject("Message from Hypha plugin: " + id);
    message.setContentType("text/plain; charset=UTF-8");
    message.setContent(content, Poco::Net::MailMessage::ENCODING_8BIT);
    try {
        Poco::Net::SMTPClientSession session(host, port);
        session.open();
        try {
            session.login(Poco::Net::SMTPClientSession::AUTH_NONE, user, password);
            session.sendMessage(message);
            session.close();
        } catch (Poco::Net::SMTPException &e) {
            Logger::warning("[EMail Plugin]["+id+"]"+e.displayText());
            session.close();
            return;
        }
    } catch (Poco::Net::NetException &e) {
        Logger::warning("[EMail Plugin]["+id+"]"+e.displayText());
        return;
    }
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(EMail)
POCO_END_MANIFEST
