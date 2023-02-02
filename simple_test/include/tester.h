//
// Created by toby on 2/1/23.
//

#ifndef MEOWTEST_TESTER_H
#define MEOWTEST_TESTER_H

#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <stdexcept>
#include <list>
#include "test_unit.h"
#include "tools.h"

inline std::string customGroup;
inline std::string customGroupDescribe;
inline std::map<std::string, TestUnitGroup> allGroups;

#define AddTestUnit(UNIT_NAME, ...) \
void TestUnit##UNIT_NAME(UnitTestFuncParams);              \
AutoRun(TestUnit##UNIT_NAME##Test,allGroups[CurrentGroup].name=CurrentGroup; allGroups[CurrentGroup].units.emplace_back(&TestUnit##UNIT_NAME,#UNIT_NAME,##__VA_ARGS__)); \
void TestUnit##UNIT_NAME(UnitTestFuncParams)

#define Group(name,...) \
extern std::string customGroup;  \
AutoRun(SetGroupName##name,customGroup=#name;allGroups[CurrentGroup].setDescribe(__VA_ARGS__);); \
namespace name{

#define GroupEnd AutoRun(UnsetGroup##name,customGroup="");};

class GroupTestContext{public:
    size_t idx = 0;
    size_t count = 0;
    size_t successCount = 0;
};

void test_group(const TestUnitGroup& group);
bool test_unit(const TestUnit& unit, GroupTestContext state);
int main();

#endif //MEOWTEST_TESTER_H
