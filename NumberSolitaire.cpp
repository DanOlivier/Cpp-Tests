#include "gtest/gtest.h"

#include <vector>
#include <bitset>
#include <algorithm>
#include <random>

using namespace std;

mt19937& prng_engine()
{
  thread_local static random_device rd{};
  thread_local static mt19937 engine{rd()};

  return engine;
}

int roll_die()
{
  thread_local static uniform_int_distribution<> dist{1, 6};
  return dist(prng_engine());
}

int solution(vector<int> &A)
{
    int N(A.size());
    if(N > 100000)
        return -1; //throw runtime_error

    vector<int> die6(6, A[0]);
    for (int i = 1; i < N; ++i)
        die6[i % 6] = *max_element(die6.begin(), die6.end()) + A[i];
    return die6[(N-1) % 6];    
}

TEST(NumberSolitaire, Trivial)
{
    {
        vector<int> A{1};
        EXPECT_EQ(solution(A), 1);
    }
    {
        vector<int> A{1,-1};
        EXPECT_EQ(solution(A), 0);
    }
    {
        vector<int> A{1,-1,1};
        EXPECT_EQ(solution(A), 2);
    }
    {
        vector<int> A{1,-1,1,-1};
        EXPECT_EQ(solution(A), 1);
    }
    {
        vector<int> A{1,-1,-1,-1,-1,1};
        EXPECT_EQ(solution(A), 2);
    }
    {
        vector<int> A{1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,1};
        EXPECT_EQ(solution(A), 3);
    }
    {
        vector<int> A{1,1,1,1,1};
        EXPECT_EQ(solution(A), 5);
    }
    {
        vector<int> A{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        EXPECT_EQ(solution(A), 16);
    }
    {
        vector<int> A{1,-2,0,9,-1,-2};
        EXPECT_EQ(solution(A), 8);
    }
}
