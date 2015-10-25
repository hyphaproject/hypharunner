#ifndef ROOTHANDLER_H
#define ROOTHANDLER_H
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
namespace hypha {
namespace plugin {
namespace video {


class RootHandler: public Poco::Net::HTTPRequestHandler {
 public:
  void handleRequest(Poco::Net::HTTPServerRequest &request,
                     Poco::Net::HTTPServerResponse &response);
};
}
}
}

#endif // ROOTHANDLER_H
