// Copyright (c) 2015-2017 Hypha
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <hypha/plugin/connection.h>
#include <hypha/utils/namesystem.h>

class Controller {
 public:
  static Controller *instance();
  void loadPlugins();
  void createConnections();

  void startThreads();
  std::string communicate(std::string id, std::string message);

 private:
  explicit Controller();
  ~Controller();

  std::shared_ptr<hypha::utils::NameSystem> namesystem;
  std::vector<std::shared_ptr<hypha::plugin::Connection>> connections;

  static Controller *singleton;
};
