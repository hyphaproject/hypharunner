#include <hypha/plugin/pluginloader.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/utils/logger.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <memory>

#include "hypharunner/controller/localconnection.h"

using namespace hypha::plugin;
using namespace hypha::handler;

LocalConnection::LocalConnection(std::string handlerId, std::string pluginId) {
    this->handler = HandlerLoader::instance()->getHandlerInstance(handlerId);
    this->plugin = PluginLoader::instance()->getPluginInstance(pluginId);
}

bool LocalConnection::connect() {
    if (handler && plugin) {
        handler->connect(boost::bind(&LocalConnection::handlerMessage, this, _1));
        plugin->connect(boost::bind(&LocalConnection::pluginMessage, this, _1));
        return true;
    } else {
        return false;
    }
}

bool LocalConnection::disconnect() {
    // not implemented yet
    return false;
}

void LocalConnection::handlerMessage(std::string message) {
    try {
        if (handlerThread) {
            if (handlerThread->joinable())
                handlerThread->join();
            delete handlerThread;
        }
        handlerThread = new std::thread([this, message] {this->plugin->receiveMessage(message); });
    } catch ( std::exception &e) {
        hypha::utils::Logger::error(e.what());
    } catch ( ... ) {
        hypha::utils::Logger::error("Error in " + plugin->getId() + " receiveMessage part.");
    }
}

void LocalConnection::pluginMessage(std::string message) {
    try {
        if (pluginThread) {
            if (pluginThread->joinable())
                pluginThread->join();
            delete pluginThread;
        }
        pluginThread = new std::thread([this, message] {this->handler->receiveMessage(message); });
    } catch ( std::exception &e) {
        hypha::utils::Logger::error(e.what());
    } catch ( ... ) {
        hypha::utils::Logger::error("Error in " + handler->getId() + " receiveMessage part.");
    }
}

std::string LocalConnection::communicate(std::string id, std::string message) {
    HyphaHandler *handler = HandlerLoader::instance()->getHandlerInstance(id);
    if (handler) {
        return handler->communicate(message);
    }
    HyphaPlugin *plugin = PluginLoader::instance()->getPluginInstance(id);
    if (plugin) {
        return plugin->communicate(message);
    }
    return "";
}
