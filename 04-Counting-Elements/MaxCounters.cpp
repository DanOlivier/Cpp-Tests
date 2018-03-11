#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// one-based indices
vector<uint> solution(uint N, const vector<uint>& A)
{
    uint max_max_counter = 0;
    uint max_counter = 0;
    unordered_map<uint, uint> counters;
    for(auto a: A)
    {
        if(a == N+1)
        {
            counters.clear();
            max_max_counter += max_counter;
            max_counter = 0;
            continue;
        }
        uint& c = counters[a-1];
        c += 1;
        max_counter = max(max_counter, c);
    }
    vector<uint> result(N);
    fill(result.begin(), result.end(), max_max_counter);
    for(auto& c: counters)
        result[c.first] += c.second;
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
