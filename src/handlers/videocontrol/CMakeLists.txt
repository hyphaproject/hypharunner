cmake_minimum_required(VERSION 3.0.0)

project(hypha-plugin-videocontrol)

find_package(Hypha COMPONENTS Utils REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")

add_library( videocontrol SHARED ${Sources} ${Headers})

target_link_libraries(videocontrol ${Hypha_LIBRARIES})

INSTALL(TARGETS videocontrol DESTINATION hypha/plugins)
