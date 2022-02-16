project(DemoApp)
find_package(Protobuf REQUIRED)
link_libraries(Boost_Log_logwrapper ${Protobuf_LIBRARIES} Boost_Asio_AsioWrapper AppBase)
include(${CMAKE_SOURCE_DIR}/cmake/source.cmake)
