#include "../include/simple_test.h"

Group(ExampleGroup)
    AddTestUnit(test1) {
        std::cout<<"ExampleGroup"<<std::endl;
    }
GroupEnd

