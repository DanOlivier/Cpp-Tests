
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits.h>

using namespace std;

double calc_avg(const vector<int>& A, int i, int j)
{
    int sum = 0;
    for(auto it = A.begin()+i; it <= A.begin()+j; it++) { sum += *it; }
    return double(sum)/(j-i+1);
}

uint count_total(const vector<uint>& P, uint x, uint y)
{
    return P[y + 1] - P[x];
}

int solution(const vector<int> &A)
{
    uint N = A.size();
    vector<uint> prefix_sum(N+1);
    int sum = 0;
    for(uint i = 0; i < N; ++i)
    {
        sum += A[i];
        prefix_sum[i+1] = sum;
    }
    //ostream_iterator<uint> out_it (cout,", ");
    //cout << "prefix_sum: " << endl;
    //copy( prefix_sum.begin(), prefix_sum.end(), out_it ); cout << endl;
    double min_avg = INT_MAX;
    uint min_i = 0, min_j = N;
    for(uint i = 0; i < N-1; ++i)
    {
        int diff = count_total(prefix_sum, i, i+1);
        double avg = double(diff)/2;
        //cout << "avg: " << avg << ", at [" << i << "-" << j << "]";// << endl;
        //cout << " calculated: " << calc_avg(A, i, j) << endl;
        if(avg < min_avg)
        {
            min_avg = avg;
            min_i = i;
            min_j = i+1;
        }
        if(i < N-2)
        {
            int diff = count_total(prefix_sum, i, i+2);
            double avg = double(diff)/3;
            if(avg < min_avg)
            {
                min_avg = avg;
                min_i = i;
                min_j = i+2;
            }
        }
    }
    //cout << "min_avg: " << min_avg << ", at (" << min_i << ", " << min_j << ")" << endl;
    return min_i;
}

#include "gtest/gtest.h"

TEST(MinAvgTwoSlice, Trivial)
{
    EXPECT_EQ(solution(vector<int>{4, 2, 2, 5, 1, 5, 8}), 1);
    EXPECT_EQ(solution(vector<int>{1, 1}), 0);
    EXPECT_EQ(solution(vector<int>{1, 3, 1}), 0);
    EXPECT_EQ(solution(vector<int>{10, 10, 1}), 1);
    EXPECT_EQ(solution(vector<int>{10, 1, 1}), 1);
    EXPECT_EQ(solution(vector<int>{10, -1, 1, 1, 1, -1}), 1);
}

