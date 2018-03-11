#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// one-based indices
vector<uint> solution(uint N, const vector<uint>& A)
{
    uint max_counter = 0;
    vector<uint> result(N);
    for(auto a: A)
    {
        if(a == N+1)
        {
            fill(result.begin(), result.end(), max_counter);
            continue;
        }
        result[a-1]++;
        max_counter = max(max_counter, result[a-1]);
    }
    return result;
}

TEST(MaxCounters, Trivial)
{
    ASSERT_EQ(solution(1, vector<uint>{1}), vector<uint>{1});
    ASSERT_EQ(solution(1, vector<uint>{1, 1}), vector<uint>{2});
    ASSERT_EQ(solution(2, vector<uint>{1, 1, 3, 1, 3}), (vector<uint>{3, 3}));
    ASSERT_EQ(solution(2, vector<uint>{1, 2, 3, 1, 3}), (vector<uint>{2, 2}));
    vector<uint> r1{3, 2, 2, 4, 2};
    ASSERT_EQ(solution(5, vector<uint>{3, 4, 4, 6, 1, 4, 4}), r1);
}
