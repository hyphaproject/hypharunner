#ifndef SENDHANDLER_H
#define SENDHANDLER_H

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>

class SendHandler: public Poco::Net::HTTPRequestHandler {
  public:
    void handleRequest(Poco::Net::HTTPServerRequest &request,
                       Poco::Net::HTTPServerResponse &response);
};

#endif // SENDHANDLER_H
