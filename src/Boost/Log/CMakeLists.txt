find_package(Boost REQUIRED COMPONENTS log)
link_libraries(${Boost_LOG_LIBRARY})
include(${CMAKE_SOURCE_DIR}/cmake/child.cmake)
AddSub()