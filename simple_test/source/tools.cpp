//
// Created by toby on 2/2/23.
//
#include <iostream>
#include "../include/tools.h"

std::string getGroupNameFromPath(const std::string &fileName,const std::string& base) {
    if (!base.empty()){
        auto first = std::string(base).size();
        return fileName.substr(first,fileName.find_first_of('.')-first);
    }

    // 如果没有定义base则将文件名作为group name
    auto first = fileName.find_last_of('/');
    if (first >= fileName.size()) {
        first = 0;
    } else {
        first++;
    }
    return fileName.substr(first, fileName.find_first_of('.') - first);
}

