#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>

using namespace std;

vector<uint> prefix_sums(const vector<uint>& A)
{
    uint n = A.size();
    vector<uint> P(n+1);
    for(uint k = 1; k < n + 1; ++k)
    {
        P[k] = P[k - 1] + A[k - 1];
    }
    return P;
}

vector<uint> suffix_sums(const vector<uint>& A)
{
    uint n = A.size();
    vector<uint> P(n+1);
    for(uint k = n; k >= 1; --k)
    {
        P[k-1] = P[k] + A[k-1];
    }
    return P;
}

TEST(PrefixSums, Trivial)
{
    ASSERT_EQ(prefix_sums(vector<uint>{1}), (vector<uint>{0, 1}));
    ASSERT_EQ(prefix_sums(vector<uint>{1, 1}), (vector<uint>{0, 1, 2}));
    ASSERT_EQ(prefix_sums(vector<uint>{1, 3, 1, 4, 2, 3, 5, 4}), (vector<uint>{0, 1, 4, 5, 9, 11, 14, 19, 23}));

    ASSERT_EQ(suffix_sums(vector<uint>{1}), (vector<uint>{1, 0}));
    ASSERT_EQ(suffix_sums(vector<uint>{1, 1}), (vector<uint>{2, 1, 0}));
    ASSERT_EQ(suffix_sums(vector<uint>{1, 3, 1, 4, 2, 3, 5, 4}), (vector<uint>{23, 22, 19, 18, 14, 12, 9, 4, 0}));
}

TEST(PrefixSums, StdLib)
{
    vector<uint> in = {1}, out(2);
    partial_sum(in.begin(), in.end(), out.begin()+1);
    ASSERT_EQ(out, (vector<uint>{0, 1}));

    vector<uint> in2 = {1, 1}, out2(3);
    partial_sum(in2.begin(), in2.end(), out2.begin()+1);
    ASSERT_EQ(out2, (vector<uint>{0, 1, 2}));
}

uint count_total(const vector<uint>& pref, uint left_pos, uint right_pos)
{
    return *(pref.begin() + right_pos + 1) - *(pref.begin() + left_pos);
}

uint mushrooms(const vector<uint>& A, uint k, uint m)
{
    uint n = A.size();
    uint result = 0;
    vector<uint> pref = prefix_sums(A);
    printf("m, k: %u, %u\n", m, k);
    printf("Going from 0 to min(m, k) + 1: 0-%u\n", min(m, k) + 1);
    for(uint p = 0; p < min(m, k) + 1; ++p)
    {
        uint left_pos = k - p; // moves to the left
        uint right_pos = min(n - 1, max(k, k + m - 2*p));
        uint sum = count_total(pref, left_pos, right_pos);
        printf("%u, %u, %u, %u\n", p, left_pos, right_pos, sum);
        result = max(result, sum);
    }
    printf("Going from 0 to min(m + 1, n - k): 0-%u\n", min(m + 1, n - k));
    for(uint p = 0; p < min(m + 1, n - k); ++p)
    {
        uint right_pos = k + p; // moves to the right
        uint left_pos = max(0u, min(k, k - (m - 2*p)));
        uint sum = count_total(pref, left_pos, right_pos);
        printf("%u, %u, %u, %u\n", p, left_pos, right_pos, sum);
        result = max(result, sum);
    }
    printf("result: %u\n", result);
    return result;
}

TEST(PrefixSums, MushroomPicker)
{
    ASSERT_EQ(mushrooms(vector<uint>{2}, 0, 1), 2);
    ASSERT_EQ(mushrooms(vector<uint>{2, 3}, 0, 1), 5);
    ASSERT_EQ(mushrooms(vector<uint>{2, 3, 1}, 1, 1), 5);
    ASSERT_EQ(mushrooms(vector<uint>{2, 3, 7, 5, 1, 3, 9}, 4, 6), 25);
}
