// Copyright (c) 2015-2016 Hypha
#pragma once

#include <Poco/Net/HTTPServer.h>

class TcpServer {
 public:
  TcpServer();
  ~TcpServer();

  void start();
  void stop();

 protected:
  Poco::Net::HTTPServer *srv;
};
