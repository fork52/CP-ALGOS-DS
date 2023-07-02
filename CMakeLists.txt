cmake_minimum_required(VERSION 3.14)
project(CP_ALGOS_DS)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Specify test and executables
add_executable(
  prime_sieve_test  
  tests/Number-Theory/test_prime_sieve.cpp
)


target_link_libraries(
  prime_sieve_test
  GTest::gtest_main
)

include(GoogleTest)
include(Dart)
gtest_discover_tests(prime_sieve_test)