// Copyright (c) 2015-2016 Hypha

#include "hypharunner/network/requesthandlerfactory.h"
#include "hypharunner/network/communicatehandler.h"
#include "hypharunner/network/infohandler.h"
#include "hypharunner/network/pointerhandler.h"
#include "hypharunner/network/roothandler.h"
#include "hypharunner/network/sendhandler.h"
#include "hypharunner/network/statusmessagehandler.h"

#include <hypha/utils/logger.h>
#include <boost/algorithm/string/predicate.hpp>

using namespace hypha::utils;

RequestHandlerFactory::RequestHandlerFactory() {}

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(
    const Poco::Net::HTTPServerRequest &request) {
  Logger::info(request.getURI());
  if (boost::starts_with(request.getURI(), "/info/"))
    return new InfoHandler();
  else if (boost::starts_with(request.getURI(), "/send/"))
    return new SendHandler();
  else if (boost::starts_with(request.getURI(), "/pointer/"))
    return new PointerHandler();
  else if (boost::starts_with(request.getURI(), "/communicate/"))
    return new CommunicateHandler();
  else if (boost::starts_with(request.getURI(), "/statusmessage/"))
    return new StatusMessageHandler();
  else
    return new RootHandler();
}
