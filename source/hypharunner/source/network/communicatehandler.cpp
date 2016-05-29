#include "hypharunner/network/communicatehandler.h"
#include <Poco/Exception.h>
#include <Poco/Net/HTMLForm.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>

using namespace hypha::utils;

void CommunicateHandler::handleRequest(
    Poco::Net::HTTPServerRequest &request,
    Poco::Net::HTTPServerResponse &response) {
  try {
    std::string message = "";
    std::string uri = request.getURI();
    std::string id = uri.substr(6, uri.find_first_of('?'));
    id = id.substr(0, id.find_first_of('/'));
    id = id.substr(0, id.find_first_of('?'));
    Logger::info("id: " + id);

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
      Logger::info(request.clientAddress().toString() +
                   " connected to CommunicateHandler_Get.");
      Poco::Net::HTMLForm form(request);
      message = form["message"];
    } else {
      Logger::info(request.clientAddress().toString() +
                   " connected to CommunicateHandler_Post.");
      std::istream &iStr = request.stream();
      std::istreambuf_iterator<char> eos;
      std::string m(std::istreambuf_iterator<char>(iStr), eos);
      message = m;
    }
    Logger::info("message: " + message);
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/json");

    std::ostream &ostr = response.send();
    hypha::handler::HyphaHandler *handler =
        hypha::handler::HandlerLoader::instance()->getHandlerInstance(id);
    hypha::plugin::HyphaPlugin *plugin =
        hypha::plugin::PluginLoader::instance()->getPluginInstance(id);
    std::string returnStr;
    if (handler) {
      returnStr = handler->communicate(message);
    } else if (plugin) {
      returnStr = plugin->communicate(message);
    } else {
      ostr << "{\"error\":true}";
    }
    Logger::info("return message: " + returnStr);
  } catch (Poco::Exception &exc) {
    Logger::error(exc.displayText());
  }
}
