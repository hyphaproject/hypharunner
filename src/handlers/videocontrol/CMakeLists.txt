cmake_minimum_required(VERSION 3.0.0)

project(hypha-plugin-videocontrol)

find_package(Hypha COMPONENTS Utils REQUIRED)
find_package(Qt5Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( videocontrol SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(videocontrol ${Hypha_LIBRARIES} Qt5::Core)

INSTALL(TARGETS videocontrol DESTINATION hypha/plugins)
