project(Algorithm_DynamicProgramming_cut)
find_package(Boost REQUIRED COMPONENTS system timer)
include(${CMAKE_SOURCE_DIR}/cmake/source.cmake)
target_link_libraries(${PROJECT_NAME} private Boost::timer Boost::system)
