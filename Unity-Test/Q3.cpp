#include <vector>
#include <iostream>

using namespace std;

int solution(int n) {
    vector<int> d;
    int l = 0;
    while (n > 0) {
        d.push_back(n % 2);
        n /= 2;
        l++;
    }
    cout << "l: " << l << ", l/2: " << l/2 << endl;
    for (int p = 1; p <= l/2; ++p) {
        cout << "p: " << p << ", l+1: " << l+1 << endl;
        bool ok = true;
        for (int i = 0; i < l - p; ++i) {
            if (d[i] != d[i + p]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return p;
        }
    }
    return -1;
}


#include <gtest/gtest.h>

TEST(Unity_Q2, Trivial)
{
    //EXPECT_EQ(solution(1), 1);
    //EXPECT_EQ(solution(3), 2);
    //EXPECT_EQ(solution(5), );
    //EXPECT_EQ(solution(7), 3);

    EXPECT_EQ(solution(10), 2);   // 1010
    EXPECT_EQ(solution(21), 2);   // 10101
    EXPECT_EQ(solution(42), 2);   // 101010
    EXPECT_EQ(solution(438), 3);  // 110110110
    EXPECT_EQ(solution(955), 4);  // 1110111011

    EXPECT_EQ(solution(2), -1);   // 10, no period?
    EXPECT_EQ(solution(5), -1);   // 101, no period?
    EXPECT_EQ(solution(11), -1);  // 1011, no period?
    EXPECT_EQ(solution(22), -1);  // 10110, no period?
    EXPECT_EQ(solution(44), -1);  // 101100, no period?
    EXPECT_EQ(solution(89), -1);  // 1011001, no period?
    EXPECT_EQ(solution(183), -1); // 10110111, no period?
}
