cmake_minimum_required(VERSION 3.0.0)

project(video)

find_package(Hypha COMPONENTS Utils REQUIRED)
find_package(OpenCV)
find_package(Boost COMPONENTS filesystem REQUIRED)

IF(OpenCV_FOUND)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    include_directories (../../)
    file (GLOB Sources "*.cpp")
    file (GLOB Headers "*.h")

    add_library( video SHARED ${Sources} ${Headers})

    target_link_libraries(video ${Hypha_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBRARIES})
    INSTALL(TARGETS video DESTINATION hypha/plugins)
ENDIF(OpenCV_FOUND)
