cmake_minimum_required(VERSION 3.0.0)

project(dht11)
find_file ( HAVE_WIRINGPI_H NAMES "wiringPi.h" PATHS ENV INCLUDE)
if(HAVE_WIRINGPI_H)
find_package(Hypha COMPONENTS Utils REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")

add_library( dht11 SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(dht11 ${Hypha_LIBRARIES} -lwiringPi)
INSTALL(TARGETS dht11 DESTINATION hypha/plugins)

endif(HAVE_WIRINGPI_H)
