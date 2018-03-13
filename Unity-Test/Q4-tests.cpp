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
    EXPECT_EQ(solution(vector<int>{7,3,7,3,1,3,4,1}), 5);
    EXPECT_EQ(solution(vector<int>{2,1,1,3,2,1,1,3}), 3);
    EXPECT_EQ(solution(vector<int>{7,5,2,7,2,7,4,7}), 6);
}

vector<int> GenerateTestVector(uint M, uint N)
{
    random_device rd;
    mt19937 g(rd());
    // set S contains unique numbers corresponding to destinations
    // we want just one single valid and complete sequence A (of M elements)
    // so we create a vector of N-M elements, filled from and array of M-1 unique numbers
    // and then add a single unique number (completing array M), and
    // add it to a random location in the original vector A
    unordered_set<int> S;
    uniform_int_distribution<int> dist{1, int(3*M)};
    for(; S.size() < M-1;) { S.insert(dist(g)); }
    
    //vector<int> S2(S.size());
    //for(auto& s: S) { s2.push_back(); } 
    //shuffle(S2.begin(), S2.end(), g);

    vector<int> A; A.reserve(N);
    uniform_int_distribution<int> dist2{0, int(S.size())-1};
    for(uint i = 0; i < N-M; ++i) 
    {
        uint k = dist2(g);
        auto s = S.begin();
        for(uint j = 0; j < k; ++j) 
            ++s;
        A.push_back(*s);
    }

    // add the last unique element
    for(; S.size() < M;) { S.insert(dist(g)); }

    // re-create the vector of elements
    //S2.clear();
    //for(auto& s: S) { S2.push_back(); } 
    //shuffle(S2.begin(), S2.end(), g);

    uniform_int_distribution<int> dist3{0, int(N-M)};
    vector<int>::iterator it = A.begin() + dist3(g);
    A.insert(it, S.begin(), S.end());
    return A;
}

TEST(Q4, Random)
{
    vector<int> A(GenerateTestVector(10, 100));
    EXPECT_EQ(solution(A), 10);

    A = GenerateTestVector(100, 1000);
    EXPECT_EQ(solution(A), 100);

    A = GenerateTestVector(1000, 10000);
    EXPECT_EQ(solution(A), 1000);
}

TEST(Q4, LargeVectorSize)
{
    EXPECT_EQ(solution(GenerateTestVector(100, 1E5)), 100);
    EXPECT_EQ(solution(GenerateTestVector(100, 1E6)), 100);
    EXPECT_EQ(solution(GenerateTestVector(100, 1E7)), 100);
    EXPECT_EQ(solution(GenerateTestVector(100, 1E8)), 100);
}

TEST(Q4, LargeKeySize)
{
    EXPECT_EQ(solution(GenerateTestVector(100, 10000)), 100);
    EXPECT_EQ(solution(GenerateTestVector(1000, 10000)), 1000);
    EXPECT_EQ(solution(GenerateTestVector(5000, 10000)), 5000);
}
