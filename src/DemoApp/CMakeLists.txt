project(DemoApp)
include(FetchContent)

FetchContent_Declare(hiredis
        GIT_REPOSITORY https://github.com/redis/hiredis.git
        GIT_TAG v1.0.0
        )

FetchContent_MakeAvailable(hiredis)

FetchContent_Declare(redis-plus-plus
        GIT_REPOSITORY https://github.com/sewenew/redis-plus-plus.git
        GIT_TAG 1.3.7
        )
FetchContent_MakeAvailable(redis-plus-plus)

target_include_directories(redis++ PRIVATE ${hiredis_SOURCE_DIR} ${hiredis_BINARY_DIR})
target_link_libraries(redis++ PRIVATE hiredis)

find_package(Protobuf REQUIRED)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS DESC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/proto/message.proto)
link_libraries(Boost_Log_logwrapper ${Protobuf_LIBRARIES} Boost_Asio_AsioWrapper AppBase)
file(GLOB_RECURSE SRCS *.cc *.cpp *.h *.hpp)
add_executable(${PROJECT_NAME} ${SRCS} ${PROTO_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE redis++ hiredis)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)