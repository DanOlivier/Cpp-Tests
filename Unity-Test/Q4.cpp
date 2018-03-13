#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <iterator>
//#include <limits.h>

using namespace std;

ostream_iterator<uint> out_it (cout,", ");

int solution(const vector<int> &A)
{
    set<int> S;
    for(auto a: A)
    {
        S.insert(a);
    }
    int N = A.size();
    int sizeS = S.size(); // number of unique elements
    S.clear();
    uint min_days = N;
    uint start = 0;
    for(int i = 0; i < N; i++)
    {
        S.insert(A[i]);
        if(S.size() == sizeS) // The set is filled, and all destinations have been visited
        {
            min_days = min(min_days, i - start);
            S.clear();
            i = start+1; // start again at one-past the previous sequence
            // Note: we could go backwards into the sequence, to start possibly closer to the end?
            // we could also maintain multiple sets, corresponding to the sequence lengths (up to the current minimum)
            start = i;
        }
    }
    return min_days;
}

#include <gtest/gtest.h>

TEST(CountDiv, Trivial)
{
    EXPECT_EQ(solution(vector<int>{7,3,7,3,1,3,4,1}), 5);
    EXPECT_EQ(solution(vector<int>{2,1,1,3,2,1,1,3}), 3);
    EXPECT_EQ(solution(vector<int>{7,5,2,7,2,7,4,7}), 6);
}
