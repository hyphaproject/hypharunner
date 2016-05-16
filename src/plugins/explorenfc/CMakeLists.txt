cmake_minimum_required(VERSION 3.0.0)

project(explorenfc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( explorenfc SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(explorenfc hypha::core hypha::utils hypha::plugin hypha::handler Qt5::Core)

file(COPY explorenfc.py DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
INSTALL(TARGETS explorenfc DESTINATION hypha/plugins)
INSTALL(FILES explorenfc.py DESTINATION hypha/plugins)
