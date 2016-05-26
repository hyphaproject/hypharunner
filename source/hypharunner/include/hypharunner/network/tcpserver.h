#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <Poco/Net/HTTPServer.h>

class TcpServer {

  public:
    TcpServer();
    ~TcpServer();

    void start();
    void stop();

  protected:
    Poco::Net::HTTPServer *srv;

};

#endif // TCPSERVER_H
