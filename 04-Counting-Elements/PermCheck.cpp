#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int solution(const vector<uint>& A)
{
    uint max_int = 0;
    unordered_set<uint> allInts;
    for(auto a: A)
    {
        if(allInts.find(a) != allInts.end())
            return 0;
        max_int = max(max_int, a);
        allInts.insert(a);
    }
    return A.size() == max_int;
}

TEST(PermCheck, Trivial)
{
    //ASSERT_EQ(solution(vector<uint>{0}, 1), 0);
    ASSERT_EQ(solution(vector<uint>{1}), 1);
    ASSERT_EQ(solution(vector<uint>{1, 1}), 0);
    ASSERT_EQ(solution(vector<uint>{1, 2}), 1);
    ASSERT_EQ(solution(vector<uint>{1, 3, 1, 4, 2, 3}), 0);
    ASSERT_EQ(solution(vector<uint>{1, 3, 5, 4, 2}), 1);
    ASSERT_EQ(solution(vector<uint>{1, 3, 4, 4, 2}), 0);
}

#include <cstdlib>      // std::rand, std::srand

#include <algorithm>
#include <random>

TEST(PermCheck, Random)
{
    srand ( unsigned ( time(0) ) );
    random_device rd;
    mt19937 g(rd());

    for(uint i =0; i < 100; ++i)
    {
        uint sz = g()%100000;
        vector<uint> v(sz);
        std::generate(v.begin(), v.end(), [n = 1] () mutable { return n++; });
        shuffle(v.begin(), v.end(), g);

        ASSERT_EQ(solution(v), 1);
    }
}
