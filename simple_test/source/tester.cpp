//
// Created by toby on 2/2/23.
//

#ifndef MEOWTEST_TESTER_CPP
#define MEOWTEST_TESTER_CPP

#include "../include/tester.h"

#include <chrono>
#include <iostream>

#include "../include/assertion.h"

void rewritable test_group(const TestUnitGroup &group) {
    std::cout << "\033[34mTesting group: " << group.name << "\033[39m" << std::endl;
    if (!group.describe.empty())
        std::cout << "\033[1;37m" << "\"\"\"\n" << group.describe << "\n\"\"\"" << "\033[39m" << std::endl;

    GroupTestContext state{.count=group.units.size()};
    for (const auto &unit: group.units) {
        if (test_unit(unit, state)) {
            state.successCount++;
            state.idx++;
            continue;
        }
        state.idx++;
    }

    if (state.successCount == state.count) {
        std::cout << "\033[1;32mAll Units Success!\033[39m\n" << std::endl;
        return;
    }
    std::cout << "\033[1;31m" << state.successCount << "/" << state.count << " Units Passed the Test!\033[39m\n"
              << std::endl;
}

bool rewritable test_unit(const TestUnit &unit, GroupTestContext state) {
    std::cout << "[" << state.idx + 1 << "/" << state.count << "]: " << "\033[1;34m" << unit.name << "\033[39m";

    if (!unit.describe.empty())
        std::cout << "\033[1;37m(" << unit.describe << ")\033[39m";
    std::cout << std::endl << "\033[1;33m";

    UnitTestContext context{};

    auto time_begin = std::chrono::system_clock::now();
    try {
        unit.unitCall(context);
    }
    catch (AssertException &e) {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now() - time_begin);
        std::cout << "\n\033[1;31mError: " << e.what() << "\033[39m(" << double(duration.count()) * 1 / 1000000
                  << "s)\n" << std::endl;
        return false;
    }
    catch (std::exception &e) {
        if (unit.type == UnitType::throwWhenErr) {
            throw _VA_LIST_DEFINED;
        }
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now() - time_begin);
        std::cout << "\n\033[1;31mError: " << e.what() << "\033[39m(" << double(duration.count()) * 1 / 1000000
                  << "s)\n" << std::endl;


        return false;
    }
    catch (...) {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now() - time_begin);
        std::cout << "\n\033[1;31mErr!Unknown exception.\033[39m" << double(duration.count()) * 1 / 1000000 << "s)\n"
                  << std::endl;

        if (unit.type == UnitType::throwWhenErr) {
            throw _VA_LIST_DEFINED;
        }

        return false;
    }
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now() - time_begin);
    std::cout << "\n\033[1;32mSuccess!";
    if (context.expectErrCount > 0) {
        std::cout << "with " << context.expectErrCount << " unexpected problems.";
    }
    std::cout << "\033[39m(" << double(duration.count()) * 1 / 1000000 << "s)\n" << std::endl;
    return true;
}

rewritable int main() {
    for (const auto &group: allGroups) {
        test_group(group.second);
    }
}


#endif //MEOWTEST_TESTER_CPP

rewritable AddTestUnitAutoRun::AddTestUnitAutoRun(UnitFunc call, const std::string &filepath, std::string name,
                                       std::string describe, UnitType type) {
//    std::cout<<"Add Unit "<<name<<std::endl;
    TestUnit unit{std::move(call), std::move(name), std::move(describe), type};
    if (currentGroup.name.empty()) {
        auto group_name = getGroupNameFromPath(filepath);
        allGroups[group_name].name = group_name;
        allGroups[group_name].units.push_back(unit);
        return;
    } else currentGroup.units.push_back(unit);
}

rewritable SetGroupAutoRun::SetGroupAutoRun(std::string name, std::string describe) {
//    std::cout<<"Add Group "<<name<<std::endl;
    currentGroup = TestUnitGroup{std::move(name), std::move(describe)};
}

PushCurrentGroupAutoRun::PushCurrentGroupAutoRun() {
//    std::cout<<"End Group "<<currentGroup.name<<std::endl;
    allGroups[currentGroup.name] = currentGroup;
    currentGroup = {};
}
