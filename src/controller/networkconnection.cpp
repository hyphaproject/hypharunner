#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/DNS.h>
#include <Poco/StreamCopier.h>
#include <iostream>
#include <hypha/plugin/pluginloader.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/settings/pluginsettings.h>
#include <hypha/settings/handlersettings.h>
#include <hypha/utils/logger.h>
#include "networkconnection.h"

using namespace hypha::utils;
using namespace hypha::plugin;
using namespace hypha::handler;
using namespace hypha::settings;

NetworkConnection::NetworkConnection(std::string handlerId, std::string pluginId) {
    this->handler = HandlerLoader::instance()->getHandlerInstance(handlerId);
    this->plugin = PluginLoader::instance()->getPluginInstance(pluginId);
    this->pluginId = pluginId;
    this->handlerId = handlerId;
}

bool NetworkConnection::connect() {
    if(handler && (HandlerSettings::instance()->getHost(handlerId) == Poco::Net::DNS::hostName() || HandlerSettings::instance()->getHost(handlerId) == "localhost")) {
        Logger::info("connection (h+p): " + handler->getId() +" + "  +pluginId);
        handler->connect(boost::bind(&NetworkConnection::receiveMessage, this, _1));
        this->id = pluginId;
        this->host = PluginSettings::instance()->getHost(id);
        return true;
    } else if(plugin && (PluginSettings::instance()->getHost(pluginId) == Poco::Net::DNS::hostName() || PluginSettings::instance()->getHost(pluginId) == "localhost")) {
        Logger::info("connection (p+h):"+plugin->getId()+"+"+handlerId);
        plugin->connect(boost::bind(&NetworkConnection::receiveMessage, this, _1));
        this->id = handlerId;
        this->host = HandlerSettings::instance()->getHost(id);
        return true;
    } else {
        return false;
    }
}

bool NetworkConnection::disconnect() {
    return false;
}

void NetworkConnection::receiveMessage(std::string message) {
    try {
        Poco::Net::HTTPClientSession session(this->host, 47965);
        session.setKeepAlive(false);

        Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, "/send/"+this->id, Poco::Net::HTTPMessage::HTTP_1_1);
        req.setContentType("application/x-www-form-urlencoded");
        req.setKeepAlive(false);

        std::string reqBody(message);
        req.setContentLength( reqBody.length() );

        std::ostream& myOStream = session.sendRequest(req);
        myOStream << reqBody;

        req.write(std::cout);

        Poco::Net::HTTPResponse res;
        std::istream& iStr = session.receiveResponse(res);
    } catch (Poco::Exception& e) {
        Logger::error(e.displayText());
    }
}

std::string NetworkConnection::communicate(std::string id, std::string message) {
    try {
        std::string host;
        HyphaHandler *handler = HandlerLoader::instance()->getHandlerInstance(id);
        if(handler) {
            host = handler->getHost();
        }
        HyphaPlugin *plugin = PluginLoader::instance()->getPluginInstance(id);
        if(plugin) {
            host = plugin->getHost();
        }

        Poco::Net::HTTPClientSession session(host, 47965);
        session.setKeepAlive(false);

        Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, "/communicate/"+id, Poco::Net::HTTPMessage::HTTP_1_1);
        req.setContentType("application/x-www-form-urlencoded");
        req.setKeepAlive(false);

        std::string reqBody(message);
        req.setContentLength( reqBody.length() );

        std::ostream& myOStream = session.sendRequest(req);
        myOStream << reqBody;

        req.write(std::cout);

        Poco::Net::HTTPResponse res;
        std::istream& iStr = session.receiveResponse(res);
        std::string returnStr;
        Poco::StreamCopier::copyToString(iStr, returnStr);
        return returnStr;
    } catch (Poco::Exception& e) {
        Logger::error(e.displayText());
    }

    return "{\"error\":true";
}
