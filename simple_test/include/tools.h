//
// Created by toby on 2/1/23.
//

#ifndef MEOWTEST_TOOLS_H
#define MEOWTEST_TOOLS_H

#include "string"

#define rewritable  __attribute__((weak))
#define autorun static __attribute__((constructor)) void

std::string getGroupNameFromPath(const std::string &fileName);

std::string currentGroupName(const std::string &fileName);

#endif //MEOWTEST_TOOLS_H
