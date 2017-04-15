// Copyright (c) 2015-2016 Hypha
#include "hypharunner/network/roothandler.h"
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>

using namespace hypha::utils;
using namespace hypha::plugin;
using namespace hypha::handler;

void RootHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  Logger::info(request.clientAddress().toString() + " connected to tcpserver.");
  response.setChunkedTransferEncoding(true);
  response.setContentType("text/html");
  std::ostream &ostr = response.send();
  ostr << "<html><head><title>HTTP Server powered by POCO C++ "
          "Libraries</title></head>";
  ostr << "<body>";
  ostr << "Handler: <br/>";
  ostr << "<ul>";
  for (HyphaHandler *handler :
       hypha::handler::HandlerLoader::instance()->getInstances()) {
    ostr << "<li><a href=\"/statusmessage/" + handler->getId() + "\">" +
                handler->getId() + "</a></li>\n";
  }
  ostr << "</ul>";
  ostr << "<br/>Plugins: <br/>";
  ostr << "<ul>";
  for (hypha::plugin::HyphaBasePlugin *plugin :
       hypha::plugin::PluginLoader::instance()->getInstances()) {
    ostr << "<li><a href=\"/statusmessage/" + plugin->getId() + "\">" +
                plugin->getId() + "</a></li>\n";
  }
  ostr << "</ul>";
  ostr << "</body></html>";
}
