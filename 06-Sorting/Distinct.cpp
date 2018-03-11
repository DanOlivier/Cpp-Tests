#include <gtest/gtest.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int solution1(const vector<int> &A)
{
    vector<int> B(A);
    sort(B.begin(), B.end());
    B.erase( unique( B.begin(), B.end() ), B.end() );
    return B.size();
}

int solution(const vector<int> &A)
{
    set<int> B(A.begin(), A.end());
    return B.size();
}

TEST(Distinct, Trivial)
{
    ASSERT_EQ(solution(vector<int>{2}), 1);
    ASSERT_EQ(solution(vector<int>{2, 5, 3}), 3);
    ASSERT_EQ(solution(vector<int>{2, 5, 5, 3}), 3);
    ASSERT_EQ(solution(vector<int>{2, 5, 5, 3, 3, 2}), 3);
}
