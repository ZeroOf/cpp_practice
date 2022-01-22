project(Boost_Asio_TestServer)
link_libraries(pthread Boost_Asio_AsioWrapper ssl crypto Boost_Log_logwrapper)
include(${CMAKE_SOURCE_DIR}/cmake/source.cmake)
