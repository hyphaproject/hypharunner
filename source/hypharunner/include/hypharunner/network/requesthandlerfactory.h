#ifndef REQUESTHANDLERFACTORY_H
#define REQUESTHANDLERFACTORY_H

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
 public:
  RequestHandlerFactory();

  Poco::Net::HTTPRequestHandler *createRequestHandler(
      const Poco::Net::HTTPServerRequest &request);
};

#endif  // REQUESTHANDLERFACTORY_H
