//
// Created by toby on 2/1/23.
//

#ifndef MEOWTEST_TOOLS_H
#define MEOWTEST_TOOLS_H

#include "string"

#if defined(__clang__) || defined(__GNUC__)
#define rewritable  __attribute__((weak))
#else
#warning msvc and others may do not allow rewriting
#define rewritable
#endif

#ifdef GROUP_BASE
std::string getGroupNameFromPath(const std::string &fileName);
#else
std::string getGroupNameFromPath(const std::string &fileName,const std::string& base={});
#endif
std::string currentGroupName(const std::string &fileName);

#endif //MEOWTEST_TOOLS_H
