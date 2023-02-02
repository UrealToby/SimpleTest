//
// Created by toby on 2/1/23.
//

#ifndef MEOWTEST_TOOLS_H
#define MEOWTEST_TOOLS_H

#include "string"

#define AutoRun(name, body)         \
static class AutoRun##name{         \
public:                             \
    AutoRun##name()                 \
    {                               \
        body;                       \
    }                               \
} autoRun##name
#define CurrentGroup currentGroupName(__FILE__)
std::string getGroupNameFromPath(const std::string &fileName);

std::string currentGroupName(const std::string &fileName);

#endif //MEOWTEST_TOOLS_H
