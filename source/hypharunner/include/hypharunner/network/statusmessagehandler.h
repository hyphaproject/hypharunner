#ifndef STATUSMESSAGEHANDLER_H
#define STATUSMESSAGEHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

class StatusMessageHandler : public Poco::Net::HTTPRequestHandler {
 public:
  void handleRequest(Poco::Net::HTTPServerRequest &request,
                     Poco::Net::HTTPServerResponse &response);
};

#endif  // STATUSMESSAGEHANDLER_H
