
file(GLOB_RECURSE SRCS *.cc *.cpp *.h *.hpp)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SRCS})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
