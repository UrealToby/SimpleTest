//
// Created by toby on 2/1/23.
//

#ifndef MEOWTEST_TEST_UNIT_H
#define MEOWTEST_TEST_UNIT_H
#include <stdexcept>
#include <list>

#define UnitTestFuncParams UnitTestContext& context
class UnitTestContext{
public:
    int expectCount = 0;
    int expectErrCount = 0;
};
using UnitFunc = std::function<void(UnitTestFuncParams)>;

enum class UnitType {
    throwWhenErr,
    shutdownWhenErr,
    continueWhenErr,
};

class TestUnit {
public:
    TestUnit() = default;

    TestUnit(UnitFunc call,
             std::string name,
             std::string describe = std::string(),
             UnitType type = UnitType::continueWhenErr) :
            unitCall{std::move(call)},
            name{std::move(name)},
            describe{std::move(describe)}, type{type} {
    }


    UnitFunc unitCall;
    std::string name;
    std::string describe;
    UnitType type;
};


class TestUnitGroup{
public:
    std::string name;
    std::string describe;
    std::list<TestUnit> units;
    void setDescribe(std::string desc=""){
        describe = std::move(desc);
    }
};

#endif //MEOWTEST_TEST_UNIT_H
