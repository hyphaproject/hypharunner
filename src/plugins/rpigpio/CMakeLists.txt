cmake_minimum_required(VERSION 2.8.11)

project(rpigpio)

find_package(Hypha COMPONENTS Utils REQUIRED)
find_package(Qt5Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( rpigpio SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(rpigpio ${Hypha_LIBRARIES} Qt5::Core)

file(COPY rpigpio.py DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
INSTALL(TARGETS rpigpio DESTINATION hypha/plugins)
INSTALL(FILES rpigpio.py DESTINATION hypha/plugins)
