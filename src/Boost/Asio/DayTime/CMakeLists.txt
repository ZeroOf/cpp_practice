project(Boost_Asio_DayTime)
include(${CMAKE_SOURCE_DIR}/cmake/source.cmake)
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
