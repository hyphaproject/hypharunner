cmake_minimum_required(VERSION 3.0.0)

project(hypha-plugin-alarm)

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

target_link_libraries(alarm hypha::core hypha::utils hypha::plugin hypha::handler)

INSTALL(TARGETS alarm DESTINATION hypha/plugins)
