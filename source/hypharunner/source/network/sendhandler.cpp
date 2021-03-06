// Copyright (c) 2015-2017 Hypha

#include "hypharunner/network/sendhandler.h"

#include <hypha/plugin/hyphareceiver.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginutil.h>
#include <hypha/utils/logger.h>

#include <Poco/Exception.h>
#include <Poco/Net/HTMLForm.h>

using namespace hypha::utils;

void SendHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
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
                   " connected to SendHandler_Get.");
      Poco::Net::HTMLForm form(request);
      message = form["message"];
    } else {
      Logger::info(request.clientAddress().toString() +
                   " connected to SendHandler_Post.");
      std::istream &iStr = request.stream();
      std::istreambuf_iterator<char> eos;
      std::string m(std::istreambuf_iterator<char>(iStr), eos);

      message = m;
    }
    Logger::info("message: " + message);
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream &ostr = response.send();
    hypha::plugin::HyphaBasePlugin *plugin =
        hypha::plugin::PluginLoader::instance()->getPluginInstance(id);
    if (plugin) {
      if (hypha::plugin::PluginUtil::isReceiver(plugin)) {
        hypha::plugin::HyphaReceiver *hr =
            dynamic_cast<hypha::plugin::HyphaReceiver *>(plugin);
        hr->receiveMessage(message);
      }
      ostr << plugin->name() << "<br/> " << plugin->getDescription();
    } else {
      ostr << "<html><head><title>HTTP Server powered by POCO C++ "
              "Libraries</title></head>";
      ostr << "<body>";
      ostr << "There is no information about this ID.";
      ostr << "</body></html>";
    }
  } catch (Poco::Exception &exc) {
    Logger::error(exc.displayText());
  }
}
