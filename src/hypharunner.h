#ifndef HYPHARUNNER_H
#define HYPHARUNNER_H

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>

class HyphaRunner : public Poco::Util::ServerApplication {
 protected:
  int main(const std::vector<std::string> &args);
  void defineOptions(Poco::Util::OptionSet &options);
  void handleHelp(const std::string &name, const std::string &value);
  void handleConfig(const std::string &name, const std::string &value);
  void displayHelp();
  bool _helpRequested = false;
};

#endif // HYPHARUNNER_H

