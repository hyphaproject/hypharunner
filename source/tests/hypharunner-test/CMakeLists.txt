
# 
# Executable name and options
# 

# Target name
set(target hypharunner-test)
message(STATUS "Test ${target}")

# 
# Sources
# 
set(hypharunner_source_path  "${PROJECT_SOURCE_DIR}/source/hypharunner/source")

set(hypharunner_sources
)

set(sources
    main.cpp
    ${hypharunner_sources}
)


# 
# Create executable
# 

# Build executable
add_executable(${target}
    ${sources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})

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
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${PROJECT_BINARY_DIR}/source/include
    ${PROJECT_SOURCE_DIR}/source/hypharunner/include
)


# 
# Libraries
# 

if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
include(CodeCoverage)
set(libgcov "gcov")

setup_target_for_coverage(${META_PROJECT_NAME}_coverage ${target} coverage)
endif()

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${Boost_LIBRARIES}
    ${Poco_LIBRARIES}
    hypha::controller hypha::core hypha::utils hypha::plugin hypha::handler
    libgmock
    ${libgcov}
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)
