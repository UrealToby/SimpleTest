//
// Created by toby on 2/2/23.
//

#ifndef SIMPLETEST_ASSERTION_H
#define SIMPLETEST_ASSERTION_H

#include <stdexcept>
#include <utility>

class AssertException : std::exception {
public:
    std::string message;

    explicit AssertException(std::string msg) : message{std::move(msg)} {};

    AssertException operator<<(const std::string &msg) {
        message += msg;
        return std::move(*this);
    }

    [[nodiscard]] const char *what() const noexcept override;
};

#define EXPECT(stmt, whenErr)           \
context.expectCount+=1;                 \
if(stmt){}                              \
else                                    \
    context.expectErrCount+=1,whenErr   \

#define EXPECT_COMPARE(left, right, sign) EXPECT((left) sign (right),std::cout << "Assert "<< #left << " " << #sign<< " " << #right << " fail!" << std::endl)
#define ASSERT_COMPARE(left, right, sign) EXPECT((left) sign (right),throw AssertException(std::string("Assert ")+ #left + " " + #sign+ " " + #right + " fail!"))

#define EXPECT_EQ(left, right) EXPECT_COMPARE(left,right,==)
#define ASSERT_EQ(left, right) ASSERT_COMPARE(left,right,==)

#define EXPECT_NE(left, right) EXPECT_COMPARE(left,right,!=)
#define ASSERT_NE(left, right) ASSERT_COMPARE(left,right,!=)

#define EXPECT_GT(left, right) EXPECT_COMPARE(left,right,>)
#define ASSERT_GT(left, right) ASSERT_COMPARE(left,right,>)

#define EXPECT_LT(left, right) EXPECT_COMPARE(left,right,<)
#define ASSERT_LT(left, right) ASSERT_COMPARE(left,right,<)

#define EXPECT_GE(left, right) EXPECT_COMPARE(left,right,>=)
#define ASSERT_GE(left, right) ASSERT_COMPARE(left,right,>=)

#define EXPECT_LE(left, right) EXPECT_COMPARE(left,right,<=)
#define ASSERT_LE(left, right) ASSERT_COMPARE(left,right,<=)

#define EXPECT_TRUE(stmt) EXPECT(stmt,std::cout << "Assert "<< #stmt << " == true fail!" << std::endl)
#define ASSERT_TRUE(stmt) EXPECT(stmt,throw AssertException(std::string("Assert ")+ #stmt + " == true fail!"))

#define EXPECT_FALSE(stmt) EXPECT(stmt,std::cout << "Assert "<< #stmt << " != true fail!" << std::endl)
#define ASSERT_FALSE(stmt) EXPECT(stmt,throw AssertException(std::string("Assert ")+ #stmt + " != true fail!"))

#define EXPECT_ERR(msg) EXPECT(stmt,std::cout << msg << std::endl)
#define ASSERT_ERR(msg) EXPECT(stmt,throw AssertException(msg))

#endif //SIMPLETEST_ASSERTION_H
