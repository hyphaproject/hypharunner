// Copyright (c) 2015-2016 Hypha

#pragma once

class Controller {
 public:
  static Controller *instance();
  void loadHandler();
  void loadPlugins();
  void createConnections();

  void startThreads();

 private:
  explicit Controller();
  ~Controller();

  static Controller *singleton;
};
