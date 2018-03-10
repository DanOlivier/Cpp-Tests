#include <vector>
#include <gtest/gtest.h>
#include <cstdlib>
#include <limits.h>

using namespace std;

int solution(const vector<int>& A)
{
    int total = 0;
    for(auto& a : A) { total += a; }
    int sumLeft = 0, minDiff = INT_MAX;
    vector<int>::const_iterator it = A.begin(), min_it = it;
    sumLeft += *it;
    total -= *it++;
    minDiff = abs(sumLeft - total);
    for(; it+1 < A.end(); ++it)
    {
        sumLeft += *it;
        total -= *it;
        int diff = abs(sumLeft - total);
        if(diff < minDiff)
        {
            minDiff = diff;
            min_it = it;
        }
    }
    return minDiff;
}

TEST(TapeEquilibrium, Trivial)
{
    vector<int> A{3, 1, 2, 4, 3};
    ASSERT_EQ(solution(A), 1);

    ASSERT_EQ(solution(vector<int>{3, 1}), 2);
    ASSERT_EQ(solution(vector<int>{3, 3, 1}), 1);
    ASSERT_EQ(solution(vector<int>{1, 3, 1}), 3);
    ASSERT_EQ(solution(vector<int>{3, 0}), 3);
    ASSERT_EQ(solution(vector<int>{0, 3, 1}), 2);
    ASSERT_EQ(solution(vector<int>{0, 0, 5, 1}), 4);
    ASSERT_EQ(solution(vector<int>{100, 0, 0, 99, 1}), 0);

    ASSERT_EQ(solution(vector<int>{-1, 1}), 2);
    ASSERT_EQ(solution(vector<int>{-1, -1}), 0);
    ASSERT_EQ(solution(vector<int>{-1, 2}), 3);
    ASSERT_EQ(solution(vector<int>{-1, 1, -1}), 1);
    ASSERT_EQ(solution(vector<int>{-1, -1, 1}), 1);

}
