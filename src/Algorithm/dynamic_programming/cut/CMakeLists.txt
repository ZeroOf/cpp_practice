project(Algorithm_DynamicProgramming_cut)
link_libraries(${Boost_SYSTEM_LIBRARY})
include(${CMAKE_SOURCE_DIR}/cmake/source.cmake)
target_link_libraries(${PROJECT_NAME} Boost::timer)
