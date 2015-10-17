cmake_minimum_required(VERSION 3.0.0)

project(espeak)

find_package(Hypha COMPONENTS Utils REQUIRED)
find_package(Qt5Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")

add_library( espeak SHARED ${Sources} ${Headers})

target_link_libraries(espeak ${Hypha_LIBRARIES} Qt5::Core)
INSTALL(TARGETS espeak DESTINATION hypha/plugins)
