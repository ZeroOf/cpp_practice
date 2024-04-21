cmake_minimum_required(VERSION 3.16)
project(cpp_practice VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(ExternalProject)

ExternalProject_Add(OpenSSL
        URL https://github.com/openssl/openssl/releases/download/openssl-3.3.0/openssl-3.3.0.tar.gz
        PREFIX ${CMAKE_BINARY_DIR}/external/openssl
        CONFIGURE_COMMAND <SOURCE_DIR>/config no-shared no-tests --prefix=<INSTALL_DIR> --openssldir=<INSTALL_DIR>
        BUILD_COMMAND $(MAKE)
        INSTALL_COMMAND $(MAKE) install
)

# After the project has been built, you can find the libraries and include directories like this:
set(OPENSSL_ROOT_DIR ${CMAKE_BINARY_DIR}/external/openssl)
set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
find_package(OpenSSL REQUIRED)
set(protobuf_BUILD_TESTS 0)
FetchContent_Declare(
        protobuf
        GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
        GIT_TAG v26.1
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(protobuf)



FetchContent_Declare(
        Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.85.0/boost-1.85.0-cmake.tar.gz
)

FetchContent_GetProperties(Boost)
if(NOT Boost_POPULATED)
    FetchContent_Populate(Boost)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE) # Force shared libs for all subprojects
    set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "" FORCE) # Enable -fPIC for all targets
    add_subdirectory(${boost_SOURCE_DIR} ${boost_BINARY_DIR})
endif()


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
set(CMAKE_BUILD_RPATH "${CMAKE_SOURCE_DIR}/third_party")
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third_party")

configure_file(src/version/version.h.in version.h)


add_subdirectory(src)
add_subdirectory(test)

# pacakge
include(InstallRequiredSystemLibraries)
include(CPack)