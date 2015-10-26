#include <hypha/utils/logger.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include "statusmessagehandler.h"

using namespace hypha::utils;

void StatusMessageHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    std::string uri = request.getURI();
    Logger::info(request.clientAddress().toString() + " connected to StatusMessageHandler.");
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
    std::string id = uri.substr(uri.find_last_of("/") + 1);
    Logger::info("id: " + id);

    hypha::handler::HyphaHandler *handler = hypha::handler::HandlerLoader::instance()->getHandlerInstance(id);
    hypha::plugin::HyphaPlugin *plugin = hypha::plugin::PluginLoader::instance()->getPluginInstance(id);

    std::ostream &ostr = response.send();
    ostr << "<html><head><title>Status Message</title></head>";
    ostr << "<body>";
    if (handler) {
        ostr << handler->name() << "<br/> " << handler->getStatusMessage();
    } else if (plugin) {
        ostr << plugin->name() << "<br/> " << plugin->getStatusMessage();
    } else {
        ostr << "There is no information about this ID.";
    }
    ostr << "</body></html>";

}
