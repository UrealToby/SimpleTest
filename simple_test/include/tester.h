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
#include <utility>
#include "test_unit.h"
#include "tools.h"

inline TestUnitGroup currentGroup;
//inline std::string customGroup;
//inline std::string customGroupDescribe;
inline std::map<std::string, TestUnitGroup> allGroups;

class AddTestUnitAutoRun {
public:
    AddTestUnitAutoRun(UnitFunc call,
                       const std::string &filepath,
                       std::string name,
                       std::string describe = std::string(),
                       UnitType type = UnitType::continueWhenErr) {
        TestUnit unit{std::move(call), std::move(name), std::move(describe), type};
        if (currentGroup.name.empty()) {
            auto group_name = getGroupNameFromPath(filepath);
            allGroups["group_name"].units.push_back(unit);
            return;
        } else currentGroup.units.push_back(unit);
    }
};


#define AddTestUnit(UNIT_NAME, ...) \
void TestUnit##UNIT_NAME(UnitTestFuncParams);              \
static AddTestUnitAutoRun add##UNIT_NAME##UnitAutoRun(&TestUnit##UNIT_NAME,__FILE__,#UNIT_NAME,##__VA_ARGS__); \
void TestUnit##UNIT_NAME(UnitTestFuncParams)

class SetGroupAutoRun {
public:
    explicit SetGroupAutoRun(std::string name, std::string describe = "") {
        currentGroup = TestUnitGroup{std::move(name), std::move(describe)};
    }
};

class PushCurrentGroupAutoRun {
public:
    explicit PushCurrentGroupAutoRun(const std::string &name) {
        allGroups[name] = currentGroup;
    }
};


#define Group(name, ...) \
extern TestUnitGroup currentGroup; \
static SetGroupAutoRun Set##name##GroupAutoRun(#name,##__VA_ARGS__); \
namespace name{

#define GroupEnd(name) static PushCurrentGroupAutoRun push##name##GroupAutoRun(#name);};

class GroupTestContext {
public:
    size_t idx = 0;
    size_t count = 0;
    size_t successCount = 0;
};

void test_group(const TestUnitGroup &group);

bool test_unit(const TestUnit &unit, GroupTestContext state);

int main();

#endif //MEOWTEST_TESTER_H
