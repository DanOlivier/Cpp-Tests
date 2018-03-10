#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <set>

using namespace std;

int solution(uint X, const vector<uint>& A)
{
    // X is the width of the river
    uint i = 0;
    set<uint> leafIndices;
    for(auto a: A)
    {
        if(a <= X)
            leafIndices.insert(a);
        if(X == leafIndices.size())
            return i;
        i += 1;
    }
    return -1;
}

TEST(FrogRiverOne, Trivial)
{
    ASSERT_EQ(solution(5, vector<uint>{1, 3, 1, 4, 2, 3, 5, 4}), 6);
    ASSERT_EQ(solution(2, vector<uint>{1, 2}), 1);
    ASSERT_EQ(solution(3, vector<uint>{1, 2}), -1);
    ASSERT_EQ(solution(1, vector<uint>{1, 2}), 0);
    ASSERT_EQ(solution(2, vector<uint>{1, 1, 1, 1, 1, 1}), -1);
    ASSERT_EQ(solution(2, vector<uint>{1, 1, 1, 1, 1, 2}), 5);
}
