#include <gtest/gtest.h>
//#include <vector>
//#include <cstdlib>
//#include <algorithm>
//#include <numeric>

using namespace std;

int solution(int A, int B, int K)
{
    for(int i = A; i <= B; )
    {
        if(i % K == 0)
        {
            return (B-i) / K + 1;
        }
        ++i;
    } 
    return 0;
}

TEST(CountDiv, Trivial)
{
    ASSERT_EQ(solution(2, 5, 3), 1);
    ASSERT_EQ(solution(3, 6, 3), 2);
    ASSERT_EQ(solution(4, 10, 5), 2);
    ASSERT_EQ(solution(20000, 30000, 1000), 11);
}