cmake_minimum_required(VERSION 3.21)

cmake_policy(SET CMP0144 NEW)

project(cpp_practice VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_BUILD_RPATH "${CMAKE_SOURCE_DIR}/third_party")
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third_party")

set(BOOST_ROOT $ENV{HOME}/3rd_party)
set(OPENSSL_ROOT_DIR $ENV{HOME}/3rd_party)

set(CMAKE_INSTALL_RPATH "$ENV{HOME}/3rd_party/lib")
set(CMAKE_BUILD_RPATH "$ENV{HOME}/3rd_party/lib;${CMAKE_SOURCE_DIR}/third_party")
set(CMAKE_PREFIX_PATH "$ENV{HOME}/3rd_party;${CMAKE_SOURCE_DIR}/third_party")

configure_file(src/version/version.h.in version.h)

find_package(Boost REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

# pacakge
include(InstallRequiredSystemLibraries)
include(CPack)