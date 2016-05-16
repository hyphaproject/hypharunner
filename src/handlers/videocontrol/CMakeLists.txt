cmake_minimum_required(VERSION 3.0.0)

project(hypha-plugin-videocontrol)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")

add_library( videocontrol SHARED ${Sources} ${Headers})

target_link_libraries(videocontrol hypha::core hypha::utils hypha::plugin hypha::handler)

INSTALL(TARGETS videocontrol DESTINATION hypha/plugins)
