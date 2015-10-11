cmake_minimum_required(VERSION 3.0.0)

project(hypha-plugin-serverstatus)

find_package(Hypha COMPONENTS Utils REQUIRED)
find_package(Qt5Core)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_FOUNDATION PocoFoundation)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( serverstatus SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(serverstatus ${Hypha_LIBRARIES} Qt5::Core)

INSTALL(TARGETS serverstatus DESTINATION hypha/plugins)
