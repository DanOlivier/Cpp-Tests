#include <gtest/gtest.h>

#include <vector>
#include <set>
#include <unordered_set>

#include <algorithm>
#include <random>

using namespace std;

int solution(const vector<int> &A);

TEST(Q4, Trivial)
{
    EXPECT_EQ(solution(vector<int>{1, 2, 3, 3, 4, 4, 4, 1}), 5); // test sliding window
    EXPECT_EQ(solution(vector<int>{7,3,7,3,1,3,4,1}), 5);
    EXPECT_EQ(solution(vector<int>{2,1,1,3,2,1,1,3}), 3);
    EXPECT_EQ(solution(vector<int>{7,5,2,7,2,7,4,7}), 6);
}

vector<int> GenerateTestVector(uint M, uint N)
{
    random_device rd;
    mt19937 g(rd());
    // vector S contains unique numbers (corresponding to "destinations")
    // we want just one subsequence of S (of size M) in A (of N elements)
    // 1. filled array S with M-1 unique (sequentially numbered) numbers
    // 1. create a vector A of N-M elements, and fill it with random elements from S
    // 2. add a single unique number to the end of S (now with size M), and
    // 3. now add S to a random location in vector A (now with size N)
    //unordered_set<int> S;
    //uniform_int_distribution<int> dist{int(-3*M), int(3*M)};
    //for(; S.size() < M-1;) { S.insert(dist(g)); }

    vector<int> S;
    uint j = 0;
    for(; j < M-1; ++j) { S.push_back(j); }
    shuffle(S.begin(), S.end(), g);

    vector<int> A; A.reserve(N);
    uniform_int_distribution<int> dist2{0, int(S.size())-1};
    for(uint i = 0; i < N-M; ++i) 
    {
        uint k = dist2(g);
        auto s = S.begin() + k;
        //auto s = S.begin(); for(uint j = 0; j < k; ++j) { ++s; }
        A.push_back(*s);
    }

    // add the last unique element
    //for(; S.size() < M;) { S.insert(dist(g)); }
    S.push_back(j);

    uniform_int_distribution<int> dist3{0, int(N-M)};
    vector<int>::iterator it = A.begin() + dist3(g);
    A.insert(it, S.begin(), S.end());
    return A;
}

ostream_iterator<uint> out_it (cout,", ");

TEST(Q4, Random)
{
    for(int i = 0; i < 100; ++i)
    {
        vector<int> A = GenerateTestVector(10, 20);
        EXPECT_EQ(solution(A), 10);
        if(solution(A) != 10)
        {
            cout << "Failed vector: ";
            copy( A.begin(), A.end(), out_it ); cout << endl;
        }
    }
    EXPECT_EQ(solution(GenerateTestVector(10, 100)), 10);
    EXPECT_EQ(solution(GenerateTestVector(100, 1000)), 100);
    EXPECT_EQ(solution(GenerateTestVector(1000, 1E4)), 1000);
}

TEST(Q4, LargeVectorSize)
{
    EXPECT_EQ(solution(GenerateTestVector(100, 1E5)), 100);
    EXPECT_EQ(solution(GenerateTestVector(100, 1E6)), 100);
    EXPECT_EQ(solution(GenerateTestVector(100, 1E7)), 100);
    //EXPECT_EQ(solution(GenerateTestVector(100, 1E8)), 100);
}

TEST(Q4, LargeKeySize)
{
    EXPECT_EQ(solution(GenerateTestVector(100, 1E4)), 100);
    EXPECT_EQ(solution(GenerateTestVector(1000, 1E4)), 1000);
    EXPECT_EQ(solution(GenerateTestVector(5000, 1E4)), 5000);
    EXPECT_EQ(solution(GenerateTestVector(1E4, 2E4)), 1E4);
    EXPECT_EQ(solution(GenerateTestVector(1E4, 1E5)), 1E4);
    EXPECT_EQ(solution(GenerateTestVector(5E4, 1E5)), 5E4);
    EXPECT_EQ(solution(GenerateTestVector(1E5, 2E5)), 1E5);
    EXPECT_EQ(solution(GenerateTestVector(5E5, 2E6)), 5E5);
    //EXPECT_EQ(solution(GenerateTestVector(5E6, 1E7)), 5E6);
}
