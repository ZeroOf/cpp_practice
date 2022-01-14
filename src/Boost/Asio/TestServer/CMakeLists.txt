project(Boost_Asio_TestServer)
link_libraries(pthread Boost_Log_logwrapper Boost_Asio_AsioWrapper ssl crypto)
include(${CMAKE_SOURCE_DIR}/cmake/source.cmake)
