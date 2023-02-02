//
// Created by toby on 2/2/23.
//

#ifndef SIMPLETEST_ASSERTION_H
#define SIMPLETEST_ASSERTION_H
#include <stdexcept>
#include <utility>

class AssertException:std::exception{
public:
    std::string message;
    explicit AssertException(std::string msg):message{std::move(msg)}{};
    AssertException operator<<(const std::string& msg){
        message+=msg;
        return std::move(*this);
    }

    [[nodiscard]] const char * what() const noexcept override;
};

#define EXPECT(stmt, whenErr)   \
if(stmt){}                  \
else                             \
    context.expectErrCount+=1,whenErr                     \


#define EXPECT_EQ(left, right) EXPECT(left==right,std::cout << "Assert "<< #left << "==" << #right << " fail!" << std::endl)

#define ASSERT_EQ(left,right) EXPECT(left==right,throw AssertException(std::string("Assert ")+ #left + "==" + #right + " fail!"))

#endif //SIMPLETEST_ASSERTION_H
