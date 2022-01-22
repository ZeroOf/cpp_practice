project(Boost_Asio_AsioWrapper)
link_libraries(Boost_Log_logwrapper)
include_directories(${CMAKE_SOURCE_DIR}/src/Boost/Log/logwrapper)
include(${CMAKE_SOURCE_DIR}/cmake/library.cmake)
