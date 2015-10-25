#include <boost/algorithm/string/predicate.hpp>
#include <hypha/utils/logger.h>
#include "roothandler.h"
#include "infohandler.h"
#include "sendhandler.h"
#include "communicatehandler.h"
#include "statusmessagehandler.h"
#include "requesthandlerfactory.h"

using namespace hypha::utils;

RequestHandlerFactory::RequestHandlerFactory() {
}

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(
  const Poco::Net::HTTPServerRequest &request) {
  Logger::info(request.getURI());
  if (boost::starts_with(request.getURI(), "/info/"))
    return new InfoHandler();
  else if (boost::starts_with(request.getURI(), "/send/"))
    return new SendHandler();
  else if (boost::starts_with(request.getURI(), "/communicate/"))
    return new CommunicateHandler();
  else if (boost::starts_with(request.getURI(), "/statusmessage/"))
    return new StatusMessageHandler();
  else
    return new RootHandler();
}
