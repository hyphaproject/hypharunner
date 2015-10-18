cmake_minimum_required(VERSION 3.0.0)

project(hypha-plugin-alarm)

find_package(Hypha COMPONENTS Utils REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")

add_library( alarm SHARED ${Sources} ${Headers})

target_link_libraries(alarm ${Hypha_LIBRARIES})

INSTALL(TARGETS alarm DESTINATION hypha/plugins)
