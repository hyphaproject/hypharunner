// Copyright (c) 2015-2016 Hypha
#pragma once

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
 public:
  RequestHandlerFactory();

  Poco::Net::HTTPRequestHandler *createRequestHandler(
      const Poco::Net::HTTPServerRequest &request);
};
