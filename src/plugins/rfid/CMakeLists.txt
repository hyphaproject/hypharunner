cmake_minimum_required(VERSION 3.0.0)

project(rfid)

find_package(Qt5SerialPort)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( rfid SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(rfid hypha::core hypha::utils hypha::plugin hypha::handler Qt5::Core)
INSTALL(TARGETS rfid DESTINATION hypha/plugins)
qt5_use_modules(rfid SerialPort)
