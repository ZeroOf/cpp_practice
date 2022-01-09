# For Windows: Prevent overriding the parent project's compiler/linker settings

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

link_libraries(gtest_main gtest gmock_main gmock pthread)
include(GoogleTest)

include(${CMAKE_SOURCE_DIR}/cmake/child_test.cmake)
AddSubTest()