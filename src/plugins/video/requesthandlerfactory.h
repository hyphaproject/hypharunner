#ifndef REQUESTHANDLERFACTORY_H
#define REQUESTHANDLERFACTORY_H
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <boost/algorithm/string/predicate.hpp>
#include "streamhandler.h"
#include "roothandler.h"
namespace hypha {
namespace plugin {
namespace video {
class Video;
class RequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory {
  public:
    RequestHandlerFactory();

    Poco::Net::HTTPRequestHandler *createRequestHandler(
        const Poco::Net::HTTPServerRequest &request);


    void setVideo(Video *video);
  protected:
    Video *video;
};
}
}
}

#endif // REQUESTHANDLERFACTORY_H
