
file(GLOB_RECURSE SRCS *.cc *.cpp *.h *.hpp)
include_directories(${PROJECT_SOURCE_DIR})
add_library(${PROJECT_NAME} ${SRCS})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
