#ifndef INFOHANDLER_H
#define INFOHANDLER_H

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"

class InfoHandler: public Poco::Net::HTTPRequestHandler {
  public:
    void handleRequest(Poco::Net::HTTPServerRequest &request,
                       Poco::Net::HTTPServerResponse &response);
};

#endif // INFOHANDLER_H
