find_package(Boost COMPONENTS coroutine)

link_libraries(${Boost_COROUTINE_LIBRARY})

include(${CMAKE_SOURCE_DIR}/cmake/child.cmake)

AddSub()