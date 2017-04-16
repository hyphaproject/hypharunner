// Copyright (c) 2015-2017 Hypha
#include "hypharunner/network/roothandler.h"

#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginutil.h>
#include <hypha/utils/logger.h>

using namespace hypha::utils;
using namespace hypha::plugin;

void RootHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                Poco::Net::HTTPServerResponse &response) {
  Logger::info(request.clientAddress().toString() + " connected to tcpserver.");
  response.setChunkedTransferEncoding(true);
  response.setContentType("text/html");
  std::ostream &ostr = response.send();
  ostr << "<html><head><title>HTTP Server powered by POCO C++ "
          "Libraries</title></head>";
  ostr << "<body>";
  ostr << "<br/>Actors: <br/>";
  ostr << "<ul>";
  for (hypha::plugin::HyphaBasePlugin *plugin :
       hypha::plugin::PluginLoader::instance()->getInstances()) {
    if (PluginUtil::isActor(plugin))
      ostr << "<li><a href=\"/statusmessage/" + plugin->getId() + "\">" +
                  plugin->getId() + "</a></li>\n";
  }
  ostr << "</ul>";
  ostr << "<br/>Handler: <br/>";
  ostr << "<ul>";
  for (hypha::plugin::HyphaBasePlugin *plugin :
       hypha::plugin::PluginLoader::instance()->getInstances()) {
    if (PluginUtil::isHandler(plugin))
      ostr << "<li><a href=\"/statusmessage/" + plugin->getId() + "\">" +
                  plugin->getId() + "</a></li>\n";
  }
  ostr << "</ul>";
  ostr << "<br/>Sensors: <br/>";
  ostr << "<ul>";
  for (hypha::plugin::HyphaBasePlugin *plugin :
       hypha::plugin::PluginLoader::instance()->getInstances()) {
    if (PluginUtil::isSensor(plugin))
      ostr << "<li><a href=\"/statusmessage/" + plugin->getId() + "\">" +
                  plugin->getId() + "</a></li>\n";
  }
  ostr << "</ul>";
  ostr << "</body></html>";
}
