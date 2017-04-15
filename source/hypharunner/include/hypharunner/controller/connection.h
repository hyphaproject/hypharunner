// Copyright (c) 2015-2016 Hypha
#pragma once

#include <string>

/**
 * @brief The Connection class
 */
class Connection {
 public:
  ~Connection();
  virtual bool connect();
  virtual bool disconnect();
  static Connection *factory(std::string senderId, std::string receiverId);
  static std::string communicate(std::string id, std::string message);
};
