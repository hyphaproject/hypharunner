// Copyright (c) 2015-2016 Hypha
#pragma once

#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>

class HyphaRunner : public Poco::Util::ServerApplication {
 public:
  HyphaRunner() {}

  ~HyphaRunner() {}

 protected:
  void initialize(Application &self);
  void uninitialize();
  int main(const std::vector<std::string> &args);
  void defineOptions(Poco::Util::OptionSet &options);
  void handleHelp(const std::string &name, const std::string &value);
  void handleExampleFile(const std::string &name, const std::string &value);
  void handleConfig(const std::string &name, const std::string &value);
  void displayHelp();
  bool _helpRequested = false;
  bool _exampleRequested = false;
};
