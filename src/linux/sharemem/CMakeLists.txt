include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_libraries(rt pthread)
include(${CMAKE_SOURCE_DIR}/cmake/child.cmake)
AddSub()