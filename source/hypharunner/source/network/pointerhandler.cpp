// Copyright (c) 2016 Hypha

#include "hypharunner/network/pointerhandler.h"

#include <Poco/Exception.h>
#include <Poco/Net/HTMLForm.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/utils/logger.h>

using namespace hypha::utils;

void PointerHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response) {
  try {
    response.setChunkedTransferEncoding(true);
    response.setContentType("text");

    std::ostream &ostr = response.send();

    ostr << "";
  } catch (Poco::Exception &exc) {
    Logger::error(exc.displayText());
  }
}
