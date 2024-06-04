project(AppBase)
link_libraries(Boost_Log_logwrapper Boost::asio Boost::interprocess)
include(${CMAKE_SOURCE_DIR}/cmake/library.cmake)
