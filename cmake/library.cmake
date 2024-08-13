
file(GLOB_RECURSE SRCS *.cc *.cpp *.h *.hpp)
add_library(${PROJECT_NAME} SHARED ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
