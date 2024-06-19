project(DemoApp)

find_package(Protobuf REQUIRED)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS DESC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/proto/message.proto)

find_package(Boost REQUIRED COMPONENTS serialization)
find_package(Absl REQUIRED)

link_libraries(Boost_Log_logwrapper Boost_Asio_AsioWrapper AppBase ${Protobuf_LIBRARIES})
file(GLOB_RECURSE SRCS *.cc *.cpp *.h *.hpp)

find_package(hiredis REQUIRED)
find_package(redis++ REQUIRED)

include_directories(${HIREDIS_INCLUDE_DIRS})
include_directories(${REDIS++_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/third_party/include)
link_directories(${CMAKE_SOURCE_DIR}/third_party/lib)

add_executable(${PROJECT_NAME} ${SRCS} ${PROTO_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE redis++ Boost::serialization Boost::boost absl::log_internal_check_op)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)