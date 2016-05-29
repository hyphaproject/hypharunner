#ifndef CONTROLLER_H
#define CONTROLLER_H

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

#endif  // CONTROLLER_H
