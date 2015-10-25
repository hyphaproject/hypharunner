#include <Poco/Net/MultipartWriter.h>
#include <Poco/Net/MessageHeader.h>
#include <Poco/Net/HTTPBasicCredentials.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

#include "video.h"
#include "streamhandler.h"

using namespace hypha::plugin::video;
void StreamHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
  if (!video->getUser().empty()) {
    if (!request.hasCredentials()) {
      response.requireAuthentication(video->getId());
      response.setContentLength(0);
      response.send();
      return;
    } else {
      Poco::Net::HTTPBasicCredentials cred(request);
      if (video->getUser() != cred.getUsername() || video->getPassword() != cred.getPassword()) {
        response.requireAuthentication(video->getId());
        response.setContentLength(0);
        response.send();
        return;
      }
    }
  }

  std::string boundary = "videostream";
  response.setChunkedTransferEncoding(false);
  response.set("Max-Age", "0");
  response.set("Expires", "0");
  response.set("Pragma", "no-cache");
  response.set("Cache-Control", "no-cache");
  response.setContentType("multipart/x-mixed-replace;boundary=--" + boundary);
  std::ostream &ostr = response.send();
  while (ostr.good()) {
    Poco::Net::MultipartWriter writer(ostr, boundary);
    Poco::Net::MessageHeader header;
    header.set("Content-Type", "image/jpeg");
    writer.nextPart(header);
    std::vector<uchar> buffer;
    cv::imencode(".jpg", video->getCurrentImage(), buffer);
    header.set("Content-Length", std::to_string(buffer.size()));
    ostr.write(reinterpret_cast<const char *> (buffer.data()), buffer.size());
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

void StreamHandler::setVideo(Video *video) {
  this->video = video;
}
