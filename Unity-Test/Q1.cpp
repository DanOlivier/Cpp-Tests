#include <string>
#include <algorithm>

using namespace std;

int solution(int N)
{
    string n = to_string(N);
    sort(n.begin(), n.end(), std::greater<char>());
    return stoi(n);
}

#include <gtest/gtest.h>

TEST(Unity_Q1, Trivial)
{
    EXPECT_EQ(solution(213), 321);
    EXPECT_EQ(solution(534), 543);
    EXPECT_EQ(solution(5394), 9543);
    EXPECT_EQ(solution(10000), 10000);
}