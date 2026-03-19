cmake_minimum_required(VERSION 3.17.5)

project(caju VERSION 1.0.1 DESCRIPTION "caju description")
set(SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF CACHE STRING "SPDLOG_ACTIVE_LEVEL")
option(BUILD_TESTS "Build CAJU tests" OFF)

set(warn_opts -Wall -Wextra -Wno-unused-parameter -Wno-implicit-fallthrough)

list(APPEND CMAKE_PREFIX_PATH $ENV{INSTALL_DIR})

message(STATUS "Install directory: $ENV{INSTALL_DIR}")

# Setup the basic C++ Compiler flags
if (APPLE)
    message(STATUS "Detecting Apple")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
endif (APPLE)

if (UNIX AND NOT APPLE)
    message(STATUS "Detecting UNIX (!Apple)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -fPIC -Wl,--no-as-needed -ldl -fpermissive")

endif ()

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL})

add_library(${CMAKE_PROJECT_NAME} SHARED
    caju/hierarchy/tiers/posix_filesystem_storage_tier.cpp
    caju/interface/native/native.cpp
    caju/thallium/thallium_engine.cpp
    caju/logger/logger.cpp
    caju/caju.cpp
)

find_package(
    thallium REQUIRED
    PATHS
    $ENV{INSTALL_DIR}
    # ${CMAKE_CURRENT_SOURCE_DIR}/local
)

find_package(
    spdlog REQUIRED
    PATHS
    $ENV{INSTALL_DIR}
    # ${CMAKE_CURRENT_SOURCE_DIR}/local
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    spdlog::spdlog
    thallium
)


target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE .)


# ---------------------------------------------------------------------------- #
# tests

if (BUILD_TESTS)
    message(STATUS "Compiling CAJU tests ...")
    enable_testing()

    function(caju_test test_file exec_file)
        get_filename_component(test_target_name "${exec_file}" NAME_WE)

        add_executable("${test_target_name}" "")
        target_sources("${test_target_name}"
            PRIVATE
            "${test_file}"
            )

        target_include_directories(${test_target_name} PRIVATE .)
        target_compile_options("${test_target_name}" PRIVATE ${warn_opts})
        target_link_libraries("${test_target_name}" ${CMAKE_PROJECT_NAME})

        add_test(NAME "${test_target_name}" COMMAND "${test_target_name}")
    endfunction(caju_test)

    caju_test("caju/hierarchy/tiers/posix_filesystem_storage_tier.test.cpp" "posix_fs_test")

endif (BUILD_TESTS)