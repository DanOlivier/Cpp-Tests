#include "gtest/gtest.h"

// you can use includes, for example:
#include <algorithm>
#include <map>
#include <limits>

using namespace std;

int solution(vector<int> &A) {
    int N(A.size());
    if(N ==0 || N > 100000)
        return -1; // throw runtime_error();
    
    // worst case if long sequences of numbers that don't recur
    map<int, int> counts;
    using pair_type = decltype(counts)::value_type;

    for(int a: A)
    {
        //if(a > numeric_limits<int>::min())
            counts[a] += 1;
        if(a < numeric_limits<int>::max())
            counts[a+1] += 1;
    }
    map<int, int>::const_iterator it = max_element(counts.begin(), counts.end(),
        [](const pair_type& p1, const pair_type& p2) {
            return p1.second < p2.second; 
        });
    return it->second;
}

TEST(LongestQuasiConstant, Trivial)
{
    vector<int> A{6, 10, 6, 9, 7, 8};
    EXPECT_EQ(solution(A), 3);
}
