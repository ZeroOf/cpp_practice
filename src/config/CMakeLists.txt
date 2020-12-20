project(config)

include(${CMAKE_SOURCE_DIR}/cmake/source.cmake)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR})