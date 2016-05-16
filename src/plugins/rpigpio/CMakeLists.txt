cmake_minimum_required(VERSION 2.8.11)

project(rpigpio)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( rpigpio SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(rpigpio hypha::core hypha::utils hypha::plugin hypha::handler Qt5::Core)

file(COPY rpigpio.py DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
INSTALL(TARGETS rpigpio DESTINATION hypha/plugins)
INSTALL(FILES rpigpio.py DESTINATION hypha/plugins)
