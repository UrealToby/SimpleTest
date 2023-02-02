//
// Created by toby on 2/2/23.
//
#include <iostream>
#include "../include/tools.h"

#ifdef GroupRoot
std::string getGroupNameFromPath(const std::string& fileName){
    auto first = std::string(GroupRoot).size();
    return fileName.substr(first,fileName.find_first_of('.')-first);
}
#else
#warning No test group root directory is defined, by default all test files are in the same directory and there are no renames

std::string getGroupNameFromPath(const std::string &fileName) {
    std::cout<<fileName;
    auto first = fileName.find_last_of('/');
    if (first >= fileName.size()) {
        first = 0;
    } else {
        first++;
    }
    return fileName.substr(first, fileName.find_first_of('.') - first);
}

#endif

