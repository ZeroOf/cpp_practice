find_package(Boost REQUIRED COMPONENTS log log_setup)
link_libraries(Boost::log Boost::log_setup)
include(${CMAKE_SOURCE_DIR}/cmake/child.cmake)
AddSub()