// Copyright (c) 2015-2017 Hypha

#include "hypharunner/controller/networkconnection.h"

#include <iostream>

#include <hypha/core/settings/pluginsettings.h>
#include <hypha/plugin/hyphasender.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>

#include <Poco/Net/DNS.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/StreamCopier.h>

using namespace hypha::utils;
using namespace hypha::plugin;
using namespace hypha::settings;

NetworkConnection::NetworkConnection(std::string senderId,
                                     std::string receiverId)
    : Connection(senderId, receiverId) {
  this->sender = PluginLoader::instance()->getPluginInstance(senderId);
  this->receiver = PluginLoader::instance()->getPluginInstance(receiverId);
  this->senderId = receiverId;
  this->receiverId = senderId;
}

bool NetworkConnection::connect(std::shared_ptr<Connection> connection) {
  if (sender &&
      (PluginSettings::instance()->getHost(senderId) ==
           Poco::Net::DNS::hostName() ||
       PluginSettings::instance()->getHost(senderId) == "localhost")) {
    Logger::info("connection (s+r): " + sender->getId() + " + " + receiverId);
    ((HyphaSender *)sender)->addListener(connection);
    //((HyphaSender *)sender)
    //    ->connect(boost::bind(&NetworkConnection::receiveMessage, this, _1));
    this->id = receiverId;
    this->host = PluginSettings::instance()->getHost(id);
    return true;
  } else {
    return false;
  }
}

bool NetworkConnection::disconnect() { return false; }

void NetworkConnection::sendMessage(std::__cxx11::string message) {
  try {
    Poco::Net::HTTPClientSession session(this->host, 47965);
    session.setKeepAlive(false);

    Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST,
                               "/send/" + this->id,
                               Poco::Net::HTTPMessage::HTTP_1_1);
    req.setContentType("application/x-www-form-urlencoded");
    req.setKeepAlive(false);

    std::string reqBody(message);
    req.setContentLength(reqBody.length());

    std::ostream &myOStream = session.sendRequest(req);
    myOStream << reqBody;

    req.write(std::cout);

    Poco::Net::HTTPResponse res;
    std::istream &iStr = session.receiveResponse(res);
  } catch (Poco::Exception &e) {
    Logger::error(e.displayText());
  }
}

std::string NetworkConnection::communicate(std::string id,
                                           std::string message) {
  try {
    std::string host;
    HyphaBasePlugin *plugin = PluginLoader::instance()->getPluginInstance(id);
    if (plugin) {
      host = plugin->getHost();
    }

    Poco::Net::HTTPClientSession session(host, 47965);
    session.setKeepAlive(false);

    Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST,
                               "/communicate/" + id,
                               Poco::Net::HTTPMessage::HTTP_1_1);
    req.setContentType("application/x-www-form-urlencoded");
    req.setKeepAlive(false);

    std::string reqBody(message);
    req.setContentLength(reqBody.length());

    std::ostream &myOStream = session.sendRequest(req);
    myOStream << reqBody;

    req.write(std::cout);

    Poco::Net::HTTPResponse res;
    std::istream &iStr = session.receiveResponse(res);
    std::string returnStr;
    Poco::StreamCopier::copyToString(iStr, returnStr);
    return returnStr;
  } catch (Poco::Exception &e) {
    Logger::error(e.displayText());
  }

  return "{\"error\":true}";
}
