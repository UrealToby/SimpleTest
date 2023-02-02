//
// Created by toby on 2/2/23.
//

#ifndef MEOWTEST_TESTER_CPP
#define MEOWTEST_TESTER_CPP

#include "../include/tester.h"
#include <chrono>
int main() {
    for (const auto &group: allGroups) {
        test_group(group.second);
    }
}

void test_group(const TestUnitGroup &group) {
    std::cout << "\033[34mTesting group: " << group.name << "\033[39m" << std::endl;
    if (!group.describe.empty())
        std::cout << "\033[1;37m" << "\"\"\"\n" << group.describe << "\n\"\"\"" << "\033[39m" << std::endl;

    TestStateUnits state{.count=group.units.size()};
    for (auto unit: group.units) {
        if (test_unit(unit, state)) {
            state.successCount++;
            state.idx++;
            continue;
        }
        state.idx++;
    }

    if (state.successCount == state.count){
        std::cout << "\033[1;32mAll Units Success!\033[39m\n"<<std::endl;
        return;
    }
    std::cout << "\033[1;31m"<< "[" << state.successCount << "/" << state.count << "]" << "Units Success!\033[39m\n"<<std::endl;
}

bool test_unit(const TestUnit &unit, TestStateUnits state) {
    std::cout << "[" << state.idx << "/" << state.count << "]: " << "\033[1;34m" << unit.name << "\033[39m";

    if (!unit.describe.empty())
        std::cout << "\033[1;37m(" << unit.describe << ")\033[39m";
    std::cout << std::endl;

    auto time_begin = std::chrono::system_clock::now();
    try {
        unit();
    }
    catch (std::exception& e) {
        auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time_begin);
        std::cout << "\033[1;31mError: "<<e.what()<<"\033[39m("<<double(duration.count()) * 1 / 1000000 <<"s)\n"<<std::endl;

        if (unit.type == UnitType::throwWhenErr) {
            throw _VA_LIST_DEFINED;
        }

        return false;
    }
    catch (...) {
        auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time_begin);
        std::cout << "\033[1;31mErr!Unknown exception.\033[39m"<<double(duration.count()) * 1 / 1000000 <<"s)\n"<<std::endl;

        if (unit.type == UnitType::throwWhenErr) {
            throw _VA_LIST_DEFINED;
        }

        return false;
    }
    auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - time_begin);
    std::cout << "\033[1;32mSuccess!\033[39m("<<double(duration.count()) * 1 / 1000000 <<"s)\n"<<std::endl;
    return true;
}

#endif //MEOWTEST_TESTER_CPP
