cmake_minimum_required(VERSION 3.0.0)

project(hypharunner)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Ldap)
find_package(Boost COMPONENTS signals thread system filesystem REQUIRED)

find_package(Poco COMPONENTS Foundation Util Net Data DataMySQL DataSQLite REQUIRED)
find_package(hypha COMPONENTS utils core handler plugin REQUIRED)


include_directories(${Boost_INCLUDE_DIRS} )

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

set(hypharunnerlibs hypha::core hypha::utils hypha::plugin hypha::handler
     ${Boost_LIBRARIES} ${Poco_LIBRARIES} )

add_executable(hypharunner "hypharunner.cpp" ${Sources} ${Headers})

target_link_libraries(hypharunner ${hypharunnerlibs})

INSTALL(TARGETS hypharunner DESTINATION hypharunner/bin)

add_subdirectory( handlers )
add_subdirectory( plugins )
