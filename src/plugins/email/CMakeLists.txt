cmake_minimum_required(VERSION 3.0.0)

project(email)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp")
file (GLOB Headers "*.h")

add_library( email SHARED ${Sources} ${Headers})

target_link_libraries(email hypha::core hypha::utils hypha::plugin hypha::handler ${Poco_LIBRARIES})
INSTALL(TARGETS email DESTINATION hypha/plugins)
