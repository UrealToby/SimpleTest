#define GroupRoot "/home/toby/Documents/CLionProjects/"
#include "../include/simple_test.h"

Group(Group1222,"A Test Unit Group")
    AddTestUnit(Test1, "A test for testing unit tests") {
        std::cout << "Hello World!"<<std::endl;
    }

    AddTestUnit(Test2) {
        std::cout << "This is the second unit test";
        std::cout<< __LINE__ <<std::endl;
    }


    AddTestUnit(Test3) {
        throw std::invalid_argument("aaa");
    }
GroupEnd(Group1222)


