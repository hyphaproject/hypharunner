// Copyright (c) 2015-2016 Hypha
#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

class Connection {
 public:
  ~Connection();
  virtual bool connect();
  virtual bool disconnect();
  static Connection *factory(std::string handlerId, std::string pluginId);
  static std::string communicate(std::string id, std::string message);
};

#endif  // CONNECTION_H
