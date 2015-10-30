cmake_minimum_required(VERSION 3.0.0)

project(pythonplugin)

find_package(Hypha COMPONENTS Utils REQUIRED)
find_library(POCO_NET PocoNet REQUIRED)
find_library(POCO_UTIL PocoUtil REQUIRED)
find_library(POCO_FOUNDATION PocoFoundation REQUIRED)
find_package( PythonLibs 2.7 REQUIRED )
find_package(Boost COMPONENTS python filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} )

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Python_Files "*.py")

add_library( ${PROJECT_NAME} SHARED ${Sources} ${Headers})

target_link_libraries(${PROJECT_NAME} ${Hypha_LIBRARIES} PocoNet PocoUtil PocoFoundation ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
file(COPY ${Python_Files} DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION hypha/plugins)
INSTALL(FILES ${Python_Files} DESTINATION hypha/plugins)
