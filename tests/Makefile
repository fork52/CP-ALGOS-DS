SRCS := $(wildcard *.cpp)
BINS := $(SRCS:%.cpp=%)

all: ${BINS}

%: %.cpp main_tests.o
	g++ --std=c++17 main_tests.o $< -o test_$@

main_tests.o: main_tests.cxx catch.hpp
	g++ --std=c++17 main_tests.cxx -c

clean:
	rm *.o test_*