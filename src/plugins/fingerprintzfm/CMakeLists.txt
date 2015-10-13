cmake_minimum_required(VERSION 3.0.0)

project(fingerprintzfm)

find_file ( HAVE_FINGERPRINTZFM_H "ZFMComm.h" PATHS ENV INCLUDE AdafruitZFM )
if(HAVE_FINGERPRINTZFM_H)
find_package(Hypha COMPONENTS Utils REQUIRED)
find_package(Qt5Core)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB Sources "*.cpp" "AdafruitZFM/*.cpp")
file (GLOB Headers "*.h" "AdafruitZFM/*.h")
file (GLOB Resources *.qrc)

QT5_ADD_RESOURCES (ResourceSources ${Resources})

add_library( fingerprintzfm SHARED ${Sources} ${Headers} ${ResourceSources})

target_link_libraries(fingerprintzfm ${Hypha_LIBRARIES} Qt5::Core)
INSTALL(TARGETS fingerprintzfm DESTINATION hypha/plugins)
endif()
