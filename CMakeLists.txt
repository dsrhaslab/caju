cmake_minimum_required(VERSION 3.17.5)

project(caju VERSION 1.0.1 DESCRIPTION "caju description")

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

add_library(${CMAKE_PROJECT_NAME} SHARED
    src/interface/native/native.cpp
    src/interface/native/posix_interface.cpp
    src/caju.cpp
)

# find_package(
#     thallium REQUIRED
#     PATHS
#     $ENV{INSTALL_DIR}
#     # ${CMAKE_CURRENT_SOURCE_DIR}/local
# )

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    # thallium
)


target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE .)


