// Copyright (c) 2015-2016 Hypha
#include "hypharunner/network/tcpserver.h"
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>
#include <hypha/utils/logger.h>
#include "hypharunner/network/requesthandlerfactory.h"

using namespace hypha::utils;

TcpServer::TcpServer() {
  Poco::UInt16 port = 47965;
  Poco::Net::HTTPServerParams *pParams = new Poco::Net::HTTPServerParams;
  pParams->setMaxQueued(100);
  pParams->setMaxThreads(16);
  Poco::Net::ServerSocket svs(port);  // set-up a server socket
  Logger::info("creating http server on port 47965");
  srv = new Poco::Net::HTTPServer(new RequestHandlerFactory(), svs, pParams);
}

TcpServer::~TcpServer() {
  stop();
  delete srv;
}

void TcpServer::start() { srv->start(); }

void TcpServer::stop() { srv->stop(); }
