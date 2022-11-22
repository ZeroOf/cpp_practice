# For Windows: Prevent overriding the parent project's compiler/linker settings

include(FetchContent)
cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

link_libraries(gtest_main gtest gmock_main gmock pthread)
include(GoogleTest)

include(${CMAKE_SOURCE_DIR}/cmake/child_test.cmake)
AddSubTest()