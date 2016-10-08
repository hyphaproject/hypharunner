// Copyright (c) 2015-2016 Hypha
#ifndef POINTERHANDLER_H
#define POINTERHANDLER_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

class PointerHandler : public Poco::Net::HTTPRequestHandler {
 public:
  void handleRequest(Poco::Net::HTTPServerRequest &request,
                     Poco::Net::HTTPServerResponse &response);
};

#endif  // POINTERHANDLER_H
