cmake_minimum_required(VERSION 3.0.0)

project(email)

find_package(Hypha COMPONENTS Utils REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_library(POCO_NET PocoNet REQUIRED)
find_library(POCO_UTIL PocoUtil REQUIRED)
find_library(POCO_FOUNDATION PocoFoundation REQUIRED)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")

add_library( email SHARED ${Sources} ${Headers})

target_link_libraries(email ${Hypha_LIBRARIES} PocoNet PocoUtil PocoFoundation)
INSTALL(TARGETS email DESTINATION hypha/plugins)
