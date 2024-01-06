cmake_minimum_required(VERSION 3.14)
project(CP_ALGOS_DS)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
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

# Advanced-Data-Structures executable
add_executable(
  advanced_data_structure_tests                  
  tests/Advanced-Data-Structures/test_merge_sort_tree.cpp
  tests/Advanced-Data-Structures/test_sparse_table.cpp
)

# Combinatorics
add_executable(
  combinatorics_tests                  
  tests/Combinatorics/test_general.cpp
)

# Tree tests executable
add_executable(
  tree_tests                  
  tests/Trees/Tries/test_tries.cpp
)

# Number Theory executable
add_executable(
  number_theory_tests                  
  tests/Number-Theory/test_prime_sieve.cpp
  tests/Number-Theory/test_sieve_factorization.cpp
  tests/Number-Theory/test_log_factorization.cpp
)

# Graph executable
add_executable(
  graph_tests  
  tests/Graphs/Undirected/DSU/test_dsu.cpp
  tests/Graphs/Directed/Binary-Lifting/test_kth_ancestor.cpp
  tests/Graphs/Directed/Binary-Lifting/test_binary_lifting.cpp
)

# Strings executable
add_executable(
  string_tests  
  tests/Strings/test_poly_hash.cpp
)

# Tree Tests
target_link_libraries(
  tree_tests
  GTest::gtest_main
)


# Number-Theory Tests
target_link_libraries(
  number_theory_tests
  GTest::gtest_main
)

# Advanced Data-Structure Tests
target_link_libraries(
  advanced_data_structure_tests  
  GTest::gtest_main
)

# Combinatorics Tests
target_link_libraries(
  combinatorics_tests  
  GTest::gtest_main
)


# Strings
target_link_libraries(
  string_tests
  GTest::gtest_main
)

# Graph tests
target_link_libraries(
  graph_tests
  GTest::gtest_main
)

include(GoogleTest)
include(Dart)

gtest_discover_tests(number_theory_tests)
gtest_discover_tests(graph_tests)
gtest_discover_tests(advanced_data_structure_tests)
gtest_discover_tests(string_tests)
gtest_discover_tests(tree_tests)
gtest_discover_tests(combinatorics_tests)