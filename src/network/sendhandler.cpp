#include <hypha/utils/logger.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Exception.h>
#include "sendhandler.h"

using namespace hypha::utils;

void SendHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
  try {
    std::string message = "";
    std::string uri = request.getURI();
    std::string id = uri.substr(6, uri.find_first_of('?'));
    id = id.substr(0, id.find_first_of('/'));
    id = id.substr(0, id.find_first_of('?'));
    Logger::info("id: " + id);

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
      Logger::info(request.clientAddress().toString() + " connected to SendHandler_Get.");
      Poco::Net::HTMLForm form(request);
      message = form["message"];
    } else {
      Logger::info(request.clientAddress().toString() + " connected to SendHandler_Post.");
      std::istream &iStr = request.stream();
      std::istreambuf_iterator<char> eos;
      std::string m(std::istreambuf_iterator<char>(iStr), eos);

      message = m;
    }
    Logger::info("message: " + message);
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream &ostr = response.send();
    hypha::handler::HyphaHandler *handler = hypha::handler::HandlerLoader::instance()->getHandlerInstance(id);
    hypha::plugin::HyphaPlugin *plugin = hypha::plugin::PluginLoader::instance()->getPluginInstance(id);
    if (handler) {
      handler->receiveMessage(message);
      ostr << handler->name() << "<br/> " << handler->getDescription();
    } else if (plugin) {
      plugin->receiveMessage(message);
    } else {
      ostr << "<html><head><title>HTTP Server powered by POCO C++ Libraries</title></head>";
      ostr << "<body>";
      ostr << "There is no information about this ID.";
      ostr << "</body></html>";
    }
  } catch (Poco::Exception &exc) {
    Logger::error(exc.displayText());
  }
}
