cmake_minimum_required(VERSION 3.0.0)

project(espeak)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")

add_library( espeak SHARED ${Sources} ${Headers})

target_link_libraries(espeak hypha::core hypha::utils hypha::plugin hypha::handler Qt5::Core)
INSTALL(TARGETS espeak DESTINATION hypha/plugins)
