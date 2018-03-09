#include "gtest/gtest.h"

#include <vector>

using namespace std;

int solution(vector<int> & A) {
    int n = A.size();
    int result = 0;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] == A[i + 1])
            result = result + 1;
    }
    int r = -1;
    for (int i = 0; i < n; i++) {
        int count = 0;
        if (i > 0) {
            if (A[i - 1] != A[i])
                count = count + 1;
            else
                count = count - 1;
        }
        if (i < n - 1) {
            if (A[i + 1] != A[i])
                count = count + 1;
            else
                count = count - 1;
        }
        r = max(r, count);
    }
    return result + r;
}


TEST(CoinAdjacency, Trivial)
{
    {
        vector<int> A{0,0};
        EXPECT_EQ(solution(A), 0);
    }
    {
        vector<int> A{1,1};
        EXPECT_EQ(solution(A), 0);
    }
    {
        vector<int> A{1,0};
        EXPECT_EQ(solution(A), 1);
    }
    {
        vector<int> A{0,1};
        EXPECT_EQ(solution(A), 1);
    }
    {
        vector<int> A{1,0,1};
        EXPECT_EQ(solution(A), 2);
    }
    {
        vector<int> A{1,0,0,1,1};
        EXPECT_EQ(solution(A), 3);
    }
    {
        vector<int> A{1,0,0,1,0,1};
        EXPECT_EQ(solution(A), 3);
    }
    {
        vector<int> A{0,1,1,0,1,0};
        EXPECT_EQ(solution(A), 3);
    }
    {
        vector<int> A{1,1,1,0,1,0,0,0,0};
        EXPECT_EQ(solution(A), 7);
    }
    {
        vector<int> A{0,0,0};
        EXPECT_EQ(solution(A), 1);
    }
    {
        vector<int> A{0,0,0,0};
        EXPECT_EQ(solution(A), 2);
    }
    {
        vector<int> A{0,0,0,0,0};
        EXPECT_EQ(solution(A), 3);
    }
    {
        vector<int> A{0,0,0,0,0,0};
        EXPECT_EQ(solution(A), 4);
    }
    {
        vector<int> A{0,0,0,0,0,1};
        EXPECT_EQ(solution(A), 5);
    }
}


