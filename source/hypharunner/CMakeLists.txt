
#
# External dependencies
#

# find_package(THIRDPARTY REQUIRED)


#
# Library name and options
#

# Target name
set(target hypharunner)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")


# Set API export file and macro
string(TOUPPER ${target} target_upper)
set(feature_file "include/${target}/${target}_features.h")
set(export_file  "include/${target}/${target}_api.h")
set(export_macro "${target_upper}_API")



#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
${include_path}/hypharunner.h
${include_path}/controller/connection.h
${include_path}/controller/controller.h
${include_path}/controller/handlerserver.h
${include_path}/controller/localconnection.h
${include_path}/controller/networkconnection.h
${include_path}/controller/pointercontroller.h
${include_path}/network/communicatehandler.h
${include_path}/network/infohandler.h
${include_path}/network/pointerhandler.h
${include_path}/network/requesthandlerfactory.h
${include_path}/network/roothandler.h
${include_path}/network/sendhandler.h
${include_path}/network/statusmessagehandler.h
${include_path}/network/tcpserver.h
)

set(sources
${source_path}/hypharunner.cpp
${source_path}/controller/connection.cpp
${source_path}/controller/controller.cpp
${source_path}/controller/handlerserver.cpp
${source_path}/controller/localconnection.cpp
${source_path}/controller/networkconnection.cpp
${source_path}/controller/pointercontroller.cpp
${source_path}/network/communicatehandler.cpp
${source_path}/network/infohandler.cpp
${source_path}/network/pointerhandler.cpp
${source_path}/network/requesthandlerfactory.cpp
${source_path}/network/roothandler.cpp
${source_path}/network/sendhandler.cpp
${source_path}/network/statusmessagehandler.cpp
${source_path}/network/tcpserver.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$"
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$"
    ${source_group} ${sources})


#
# Create executable
#

# Build executable
add_executable(${target}
    MACOSX_BUNDLE
    ${sources}
    ${headers}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# Create feature detection header
# Compilers: https://cmake.org/cmake/help/v3.1/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE_%3CLANG%3E_COMPILER_ID
# Feature: https://cmake.org/cmake/help/v3.1/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html

# Check for availability of module; use pre-generated version if not found
if (WriterCompilerDetectionHeaderFound)
    write_compiler_detection_header(
        FILE ${feature_file}
        PREFIX ${target_upper}
        COMPILERS AppleClang Clang GNU MSVC
        FEATURES cxx_alignas cxx_alignof cxx_constexpr cxx_final cxx_noexcept cxx_nullptr cxx_sizeof_member cxx_thread_local
        VERSION 3.2
    )
else()
    file(
        COPY ${PROJECT_SOURCE_DIR}/codegeneration/${target}_features.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/${target}
        USE_SOURCE_PERMISSIONS
    )
endif()


#
# Project options
#

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


#
# Include directories
#

target_include_directories(${target}
    PRIVATE
    ${PROJECT_BINARY_DIR}/source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include

    PUBLIC
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${Boost_INCLUDE_DIR}
    ${Poco_INCLUDE_DIR}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


#
# Libraries
#

target_link_libraries(${target}
    PRIVATE
    PUBLIC
    ${DEFAULT_LIBRARIES}
    ${Boost_LIBRARIES}
    ${Poco_LIBRARIES}
    hypha::controller hypha::core hypha::utils hypha::plugin hypha::handler
    INTERFACE
)


#
# Compile definitions
#

target_compile_definitions(${target}
    PRIVATE

    PUBLIC
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_upper}_STATIC_DEFINE>
    ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE
)


#
# Compile options
#

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)


#
# Linker options
#

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)


#
# Deployment
#

# Library
install(TARGETS ${target}
    EXPORT  "${target}-export"            COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT dev
)

# Header files
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# Generated header files
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# CMake config
install(EXPORT ${target}-export
    NAMESPACE   ${META_PROJECT_NAME}::
    DESTINATION ${INSTALL_CMAKE}/${target}
    COMPONENT   dev
)
