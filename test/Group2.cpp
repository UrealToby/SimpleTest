#define GroupRoot "/home/toby/Documents/CLionProjects/"

#include "../include/simple_test.h"

namespace Group2{
    AddTestUnit(Test1, "A test for testing unit tests") {
        std::cout << "Hello World!"<<std::endl;
    }

    AddTestUnit(Test2) {
        std::cout << "This is the second unit test";
        std::cout<< __LINE__ <<std::endl;
    }


    AddTestUnit(Test3) {

    }
}



