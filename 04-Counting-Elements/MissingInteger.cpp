#include <gtest/gtest.h>
#include <vector>
#include <set>

using namespace std;

int solution(const vector<int>& A)
{
    set<int> allInts; // keep them sorted
    for(auto a: A)
    {
        if(a > 0)
            allInts.insert(a);
    }
    uint i = 1;
    auto it = allInts.begin(), it2 = allInts.end();
    for(; it != it2; ++it, ++i)
    {
        if(*it != i)
            return i;
    }
    return i;
}

TEST(MissingInteger, Trivial)
{
    ASSERT_EQ(solution(vector<int>{1, 3, 6, 4, 1, 2}), 5);

    ASSERT_EQ(solution(vector<int>{1, 2, 3}), 4);
    ASSERT_EQ(solution(vector<int>{-1, -3}), 1);
    ASSERT_EQ(solution(vector<int>{-1, -3, 5, 4, 3, 2, 1}), 6);
}
