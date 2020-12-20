cmake_minimum_required(VERSION 3.16)
project(cpp_practice VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_INSTALL_RPATH "$ENV{HOME}/3rd_party/lib")
set(CMAKE_BUILD_RPATH "$ENV{HOME}/3rd_party/lib")

configure_file(src/config/version.h.in version.h)

set(BOOST_ROOT $ENV{HOME}/3rd_party)
message("${BOOST_ROOT}")
include_directories(INTERFACE $ENV{HOME}/3rd_party/include)
link_directories($ENV{HOME}/3rd_party/lib)

add_subdirectory(src)

# pacakge
include(InstallRequiredSystemLibraries)
include(CPack)