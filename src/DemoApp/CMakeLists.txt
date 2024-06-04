project(DemoApp)

#find_package(Protobuf REQUIRED)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR})
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS DESC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/proto/message.proto)

set(PROTOC $<TARGET_FILE:protoc>)
set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)
set(PROTO_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Define the output source and header files for the .proto file
set(PROTO_SRCS ${PROTO_BUILD_DIR}/message.pb.cc)
set(PROTO_HDRS ${PROTO_BUILD_DIR}/message.pb.h)

add_custom_command(
        OUTPUT ${PROTO_SRCS} ${PROTO_HDRS}
        COMMAND ${PROTOC} --proto_path=${PROTO_SRC_DIR} --cpp_out=${PROTO_BUILD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/proto/message.proto
        DEPENDS ${PROTOC} ${CMAKE_CURRENT_SOURCE_DIR}/proto/message.proto
)

link_libraries(Boost_Log_logwrapper protobuf::libprotobuf Boost_Asio_AsioWrapper AppBase)
file(GLOB_RECURSE SRCS *.cc *.cpp *.h *.hpp)

find_package(hiredis REQUIRED)
find_package(redis++ REQUIRED)

include_directories(${HIREDIS_INCLUDE_DIRS})
include_directories(${REDIS++_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/third_party/include)
link_directories(${CMAKE_SOURCE_DIR}/third_party/lib)

add_executable(${PROJECT_NAME} ${SRCS} ${PROTO_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE redis++ Boost::serialization Boost::redis)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)