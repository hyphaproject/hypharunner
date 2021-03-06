// Copyright (c) 2015-2017 Hypha

#include "hypharunner/network/statusmessagehandler.h"

#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>

using namespace hypha::utils;

void StatusMessageHandler::handleRequest(
    Poco::Net::HTTPServerRequest &request,
    Poco::Net::HTTPServerResponse &response) {
  std::string uri = request.getURI();
  Logger::info(request.clientAddress().toString() +
               " connected to StatusMessageHandler.");
  response.setChunkedTransferEncoding(true);
  response.setContentType("text/html");
  std::string id = uri.substr(uri.find_last_of("/") + 1);
  Logger::info("id: " + id);

  hypha::plugin::HyphaBasePlugin *plugin =
      hypha::plugin::PluginLoader::instance()->getPluginInstance(id);

  std::ostream &ostr = response.send();
  ostr << "<html><head><title>Status Message</title></head>";
  ostr << "<body>";
  if (plugin) {
    ostr << plugin->name() << "<br/> " << plugin->getStatusMessage();
  } else {
    ostr << "There is no information about this ID.";
  }
  ostr << "</body></html>";
}
