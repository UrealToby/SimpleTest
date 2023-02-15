cmake_minimum_required(VERSION 3.25)
project(BuildLib)
project(TestSimpleTest)

set(CMAKE_CXX_STANDARD 17)

add_library(BuildLib STATIC simple_test/include/tester.h simple_test/include/test_unit.h simple_test/include/tools.h simple_test/source/tester.cpp simple_test/source/tools.cpp simple_test/source/assertion.cpp simple_test/include/assertion.h)

# 指定动态库的输出名称
SET_TARGET_PROPERTIES(BuildLib PROPERTIES OUTPUT_NAME "simple_test")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

INSTALL(FILES simple_test/include/assertion.h simple_test/include/test_unit.h simple_test/include/tester.h simple_test/include/tools.h simple_test/include/simple_test.h DESTINATION include)
INSTALL(TARGETS BuildLib
        ARCHIVE DESTINATION lib
        )

add_executable(TestSimpleTest simple_test/include/tester.h simple_test/include/test_unit.h simple_test/include/tools.h simple_test/source/tester.cpp simple_test/source/tools.cpp simple_test/source/assertion.cpp simple_test/include/assertion.h test/test1.cpp test/test2.cpp)
target_include_directories(TestSimpleTest PRIVATE simple_test/include)
