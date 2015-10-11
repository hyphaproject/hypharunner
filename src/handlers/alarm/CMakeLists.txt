cmake_minimum_required(VERSION 3.0.0)

project(hypha-plugin-alarm)

find_package(Hypha COMPONENTS Utils REQUIRED)
find_package(Qt5Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( alarm SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(alarm ${Hypha_LIBRARIES} Qt5::Core)

INSTALL(TARGETS alarm DESTINATION hypha/plugins)
