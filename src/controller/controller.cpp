#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>
#include <mutex>
#include <hypha/utils/logger.h>
#include <hypha/database/database.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/handler/handlerloader.h>
#include "connection.h"
#include "controller.h"

using namespace hypha::utils;
using namespace hypha::plugin;
using namespace hypha::handler;
using namespace hypha::database;

Controller *Controller::singleton = 0;

Controller::Controller() {
}

Controller::~Controller() {

}

Controller *Controller::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();

        if (!singleton)
            singleton = new Controller();
        mutex.unlock();
    }

    return singleton;
}

void Controller::loadHandler() {
    HandlerLoader::instance()->loadLocalInstances();
}

void Controller::loadPlugins() {
    PluginLoader::instance()->loadLocalInstances();
}

void Controller::createConnections() {
    Poco::Data::Statement statement = Database::instance()->getStatement();
    statement << "SELECT id,handler_id,plugin_id  FROM connection";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while (more) {
        try {
            std::string handlerId = rs[1].convert<std::string>();
            std::string pluginId = rs[2].convert<std::string>();
            Connection *connection = Connection::factory( handlerId, pluginId);
            connection->connect();
        } catch (std::exception &ex) {
            Logger::error(ex.what());
        }
        more = rs.moveNext();
    }
}

void Controller::startThreads() {
    for (HyphaHandler *handler : HandlerLoader::instance()->getInstances()) {
        Logger::info("start thread (h): " + handler->getId());
        handler->start();
    }
    for (HyphaPlugin *plugin : PluginLoader::instance()->getInstances()) {
        Logger::info("start thread (p): " + plugin->getId());
        plugin->setCallMessageFunction(Connection::communicate);
        plugin->setup();
    }
    for (HyphaPlugin *plugin : PluginLoader::instance()->getInstances()) {
        plugin->start();
    }
}

