#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING 
#include "doctest.h"

int add(int a, int b){
    return a + b;
}

TEST_CASE("Testing Add function"){
    CHECK(add(1, 2) == 3);
    CHECK(add(1, 15) == 17);
}

