project(DemoAppBase)
find_package(Protobuf REQUIRED)
link_libraries(Boost_Log_logwrapper AppBase ${Protobuf_LIBRARIES})
include(${CMAKE_SOURCE_DIR}/cmake/library.cmake)
