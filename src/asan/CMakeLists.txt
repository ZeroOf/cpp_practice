project(asan)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
include(${CMAKE_SOURCE_DIR}/cmake/source.cmake)
