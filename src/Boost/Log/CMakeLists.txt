find_package(Boost REQUIRED COMPONENTS log log_setup)
link_libraries(${Boost_LOG_LIBRARY} ${Boost_LOG_SETUP_LIBRARY})
include(${CMAKE_SOURCE_DIR}/cmake/child.cmake)
AddSub()