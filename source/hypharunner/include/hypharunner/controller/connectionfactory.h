// Copyright (c) 2015-2016 Hypha
#pragma once

#include <memory>
#include <string>

#include <hypha/plugin/connection.h>
#include <hypha/utils/namesystem.h>

/**
 * @brief The Connection class
 */
class ConnectionFactory {
 public:
  ~ConnectionFactory();
  static std::shared_ptr<hypha::plugin::Connection> factory(std::string senderId, std::string receiverId);
  static std::string communicate(std::string id, std::string message);
};
