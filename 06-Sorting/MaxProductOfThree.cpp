#include <gtest/gtest.h>

#include <vector>
#include <algorithm>

using namespace std;

int solution(const vector<int> &A)
{
    vector<int> B(A);
    sort(B.begin(), B.end(), [=](int a, int b) {
        return a > b; 
    });
    vector<int> C(A);
    sort(C.begin(), C.end(), [=](int a, int b) {
        return abs(a) > abs(b); 
    });

    auto first = B.begin();
    auto last = B.end()-1;
    auto p1 = *(first) * (*(first+1)) * (*(first+2));
    auto p2 = (*(first)) * (*last) * (*(last-1));
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
