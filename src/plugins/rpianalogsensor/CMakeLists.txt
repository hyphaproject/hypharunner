cmake_minimum_required(VERSION 3.0.0)

project(rpianalogsensor)
find_file ( HAVE_WIRINGPI_H "wiringPi.h" PATHS ENV INCLUDE)
if(HAVE_WIRINGPI_H)

find_package(Hypha COMPONENTS Utils REQUIRED)
find_package(Qt5Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( rpianalogsensor SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(rpianalogsensor ${Hypha_LIBRARIES} Qt5::Core -lwiringPi)
file(COPY rpianalogsensor.py DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
INSTALL(TARGETS rpianalogsensor DESTINATION hypha/plugins)
INSTALL(FILES rpianalogsensor.py DESTINATION hypha/plugins)
endif(HAVE_WIRINGPI_H)
