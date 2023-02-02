cmake_minimum_required(VERSION 3.25)
project(SimpleTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimpleTest simple_test/include/tester.h simple_test/include/test_unit.h simple_test/include/tools.h test/test1.cpp simple_test/source/tester.cpp simple_test/source/tools.cpp test/test2.cpp include/simple_test.h include/simple_test.h simple_test/source/assertion.cpp simple_test/include/assertion.h)
