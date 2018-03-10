#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>

using namespace std;

int div_ceil(int numerator, int denominator)
{
        div_t res = div(numerator, denominator);
        return res.rem ? (res.quot + 1) : res.quot;
}

int solution(int X, int Y, int D)
{
    /*
    int i = 0;
    while(X < Y)
    {
        X += D;
        i++;
    }
    return i;
    */
    return div_ceil((Y - X),  D);
}

TEST(FrogJmp, Trivial)
{
    ASSERT_EQ(solution(10, 85, 30), 3);
    ASSERT_EQ(solution(1, 10, 5), 2);
    ASSERT_EQ(solution(1, 100, 10), 10);
    ASSERT_EQ(solution(1, 101, 10), 10);
    ASSERT_EQ(solution(1, 102, 10), 11);
    ASSERT_EQ(solution(1, 1000000000, 1000000000), 1);
    ASSERT_EQ(solution(1, 1000000000,  999999999), 1);
    ASSERT_EQ(solution(1, 1000000000,  999999998), 2);
}
