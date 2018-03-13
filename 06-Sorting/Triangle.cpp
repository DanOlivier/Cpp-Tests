#include <vector>
#include <set>
#include <algorithm>
#include <sys/types.h>
//#include <stdio.h>

using namespace std;

int solution(const vector<int> &B)
{
    uint N = B.size();
    if(N < 3)
        return 0;
    vector<int> A(B);
    sort(A.begin(), A.end(), greater<int>());

    for(uint i = 0; i <= N-2; i++)
    {
        //printf("(%d, %u, %u)\n", i, j, k);
        bool b1 = (A[i]   < long(A[i+1]) + A[i+2]);
        // With the array sorted, if the 1st inequality holds,
        // the other two are guaranteed to also be true
        //bool b2 = (A[i+1] < long(A[i+2]) + A[i]);
        //bool b3 = (A[i+2] < long(A[i])   + A[i+1]);
        if(b1)// && b2 && b3)
        {
            //printf("result: %d\n", 1);
            return 1;
        }
    }

    //printf("result: %d\n", 0);
    return 0;
}

#include <gtest/gtest.h>
#include <limits.h>

TEST(Triangle, Trivial)
{
    EXPECT_EQ(solution(vector<int>{1,1,1}), 1);
    EXPECT_EQ(solution(vector<int>{INT_MAX,INT_MAX,INT_MAX}), 1);
    EXPECT_EQ(solution(vector<int>{10,50,1}), 0);
    EXPECT_EQ(solution(vector<int>{10,2,5,1,8,20}), 1);
    EXPECT_EQ(solution(vector<int>{10,50,5,1}), 0);
}

