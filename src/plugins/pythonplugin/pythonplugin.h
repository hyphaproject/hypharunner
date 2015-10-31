#ifndef PYTHONPLUGIN_H
#define PYTHONPLUGIN_H

#include <boost/python.hpp>
#include <hypha/plugin/hyphaplugin.h>
namespace hypha {
namespace plugin {
namespace pythonplugin {
class PythonPlugin : public HyphaPlugin {
  public:
    void doWork();
    void setup();
    std::string name() {
        return "pythonplugin";
    }
    std::string getTitle() {
        return "Python Plugin";
    }
    std::string getVersion() {
        return "0.1";
    }
    std::string getDescription() {
        return "Plugin to use Python code.";
    }
    void loadConfig(std::string json);
    std::string getConfig();
    HyphaPlugin *getInstance(std::string id);

    void receiveMessage(std::string message);
    std::string communicate(std::string message);
    std::string parse_python_exception();

  protected:
    std::string config;
    std::string pythonmodule;
    std::string pythonclass;
    boost::python::object main;
    boost::python::object global;
    boost::python::object result;
    boost::python::object py_class;
};
}
}
}
#endif // PYTHONPLUGIN_H
