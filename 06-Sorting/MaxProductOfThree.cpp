#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

using namespace std;

int solution(const vector<int> &A)
{
    uint N = A.size();
    vector<int> B(A);
    sort(B.begin(), B.end(), [=](int a, int b) {
        return a > b; 
    });

    int p1 = B[0] * B[1] * B[2];
    int p2 = B[0] * B[N-1] * B[N-2];
    return max(p1, p2);
}

TEST(MaxProductOfThree, Trivial)
{
    ASSERT_EQ(solution(vector<int>{2, 5, 3}), 30);
    ASSERT_EQ(solution(vector<int>{2, 5, 5, 3}), 75);
    ASSERT_EQ(solution(vector<int>{2, 5, 5, 3, 3, 20, 100, 1000}), 2000000);

    ASSERT_EQ(solution(vector<int>{-2, 5, -3}), 30);
    ASSERT_EQ(solution(vector<int>{2, -5, -3}), 30);
    ASSERT_EQ(solution(vector<int>{-2, -5, -3}), -30);
    ASSERT_EQ(solution(vector<int>{-5, 5, -5, 4}), 125);

    ASSERT_EQ(solution(vector<int>{-5, 5, 5, 4}), 100);
    ASSERT_EQ(solution(vector<int>{-5, -5, 5, -4}), 125);
    ASSERT_EQ(solution(vector<int>{-5, -4, 5, 3}), 100);
}
