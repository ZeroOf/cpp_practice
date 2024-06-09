project(AppBase)
find_package(Boost REQUIRED COMPONENTS system)
include(${CMAKE_SOURCE_DIR}/cmake/library.cmake)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost_Log_logwrapper Boost::system)