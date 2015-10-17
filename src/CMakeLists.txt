cmake_minimum_required(VERSION 3.0.0)

project(hypharunner)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Hypha COMPONENTS Utils Core Handler Plugin REQUIRED)
#find_package(Poco REQUIRED)
find_library(POCO_DATA PocoData)
find_library(POCO_MYSQL PocoMySQL)
find_library(POCO_SQLITE PocoSQLite)
find_library(POCO_NET PocoNet)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_FOUNDATION PocoFoundation)

find_package(Ldap)
find_package(Boost COMPONENTS signals thread system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${Poco_INCLUDE_DIRS} ${Hypha_INCLUDE_DIRS})

IF(WIN32)
    include_directories( "C:/poco/Net/include" "C:/poco/Foundation/include"
        "C:/poco/Util/include" "C:/poco/Data/include" "C:/poco/Data/MySQL/include")
    link_directories( "C:/poco/lib" "C:/Dev/Hypha/lib" )
else()
ENDIF(WIN32)

file (GLOB Sources "controller/*.cpp" "network/*.cpp"
        "plugin/*cpp" "handler/*.cpp")
file (GLOB Headers "*.h" "controller/*.h" "network/*.h"
        "plugin/*.h" "handler/*.h")

set(hypharunnerlibs ${Hypha_LIBRARIES}
# HyphaUtils HyphaCore HyphaHandler HyphaPlugin
     ${Boost_LIBRARIES} ${Poco_LIBRARIES} PocoNet PocoUtil PocoFoundation PocoData PocoMySQL PocoSQLite)

add_executable(hypharunner "hypharunner.cpp" ${Sources} ${Headers})

target_link_libraries(hypharunner ${hypharunnerlibs})

INSTALL(TARGETS hypharunner DESTINATION hypharunner/bin)

add_subdirectory( handlers )
add_subdirectory( plugins )
