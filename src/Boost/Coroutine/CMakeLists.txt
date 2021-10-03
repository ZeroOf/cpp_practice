find_package(Boost COMPONENTS coroutine)

message("coroutine ${Boost_COROUTINE_LIBRARY}")

link_libraries(${Boost_COROUTINE_LIBRARY})

include(${CMAKE_SOURCE_DIR}/cmake/child.cmake)

AddSub()