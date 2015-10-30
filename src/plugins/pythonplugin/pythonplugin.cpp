#include <Poco/ClassLibrary.h>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/utils/logger.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include "pythonplugin.h"

namespace py = boost::python;
using namespace boost::python;
using namespace hypha::plugin;
using namespace hypha::plugin::pythonplugin;

void PythonPlugin::doWork() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    try {
        boost::python::object py_doWork = py_class.attr("doWork");
        if(!py_doWork.is_none())
        {
            py_doWork();
        }
    } catch(...) {
        std::string python_error = parse_python_exception();
        hypha::utils::Logger::error(python_error);
    }
}

void PythonPlugin::setup() {
    try {
        Py_Initialize();

        main = import("__main__");
        global = main.attr("__dict__");
        result = exec_file("../plugins/pythonbaseplugin.py", global, global);
        result = exec("import sys", global, global);
        result = exec("sys.path.append(\"../plugins/\")", global, global);
        result = exec("import pythonbaseplugin", global, global);
        py_class = boost::python::eval("pythonbaseplugin.PythonBasePlugin()", global, global);

        // load config
        boost::python::object py_loadConfig = py_class.attr("loadConfig");
        if(!py_loadConfig.is_none())
        {
            py_loadConfig(config);
        }
    } catch(std::exception &e) {
        std::string python_error = parse_python_exception();
        hypha::utils::Logger::error(python_error);
        hypha::utils::Logger::error(e.what());
    } catch(...) {
        std::string python_error = parse_python_exception();
        hypha::utils::Logger::error(python_error);
    }
}

std::string PythonPlugin::communicate(std::string message) {
    std::string ret;
    try {
        boost::python::object py_communicate = py_class.attr("communicate");
        if(!py_communicate.is_none())
        {
            ret = boost::python::extract<std::string>(py_communicate(message));
        }
    } catch(...) {
        std::string python_error = parse_python_exception();
        hypha::utils::Logger::error(python_error);
    }
    return ret;
}

std::string PythonPlugin::parse_python_exception()
{
    PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
    PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);
    std::string ret("Unfetchable Python error");
    if(type_ptr != NULL){
        py::handle<> h_type(type_ptr);
        py::str type_pstr(h_type);
        py::extract<std::string> e_type_pstr(type_pstr);
        if(e_type_pstr.check())
            ret = e_type_pstr();
        else
            ret = "Unknown exception type";
    }
    if(value_ptr != NULL){
        py::handle<> h_val(value_ptr);
        py::str a(h_val);
        py::extract<std::string> returned(a);
        if(returned.check())
            ret +=  ": " + returned();
        else
            ret += std::string(": Unparseable Python error: ");
    }
    if(traceback_ptr != NULL){
        py::handle<> h_tb(traceback_ptr);
        py::object tb(py::import("traceback"));
        py::object fmt_tb(tb.attr("format_tb"));
        py::object tb_list(fmt_tb(h_tb));
        py::object tb_str(py::str("\n").join(tb_list));
        py::extract<std::string> returned(tb_str);
        if(returned.check())
            ret += ": " + returned();
        else
            ret += std::string(": Unparseable Python traceback");
    }
    return ret;
}

void PythonPlugin::loadConfig(std::string json) {
    this->config = json;
}

std::string PythonPlugin::getConfig() {
    return "{}";
}

hypha::plugin::HyphaPlugin *PythonPlugin::getInstance(std::string id) {
    PythonPlugin *instance = new PythonPlugin();
    instance->setId(id);
    return instance;
}

void PythonPlugin::receiveMessage(std::string message) {
    try {
        boost::python::object py_receiveMessage = py_class.attr("receiveMessage");
        if(!py_receiveMessage.is_none())
        {
            py_receiveMessage(message);
        }
    } catch(...) {
        std::string python_error = parse_python_exception();
        hypha::utils::Logger::error(python_error);
    }
}

POCO_BEGIN_MANIFEST(HyphaPlugin)
POCO_EXPORT_CLASS(PythonPlugin)
POCO_END_MANIFEST
