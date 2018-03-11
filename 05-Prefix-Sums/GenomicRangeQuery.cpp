#include "gtest/gtest.h"

#include <vector>
#include <string>
#include <limits.h>
#include <stdexcept>
#include <algorithm>

using namespace std;

uint get_impact(char c)
{
    switch(c)
    {
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
    default:
        throw runtime_error("Invalid nucleotide character");
    }
}

uint min_impact(const string& S, uint p, uint q)
{
    uint min_impact = INT_MAX;
    for_each(S.begin() + p, S.begin() + q + 1, [&](char c){
        min_impact = min(min_impact, get_impact(c));
    });
    return min_impact;
}

vector<uint> solution(const string& S, const vector<uint>& P, const vector<uint>& Q)
{
    uint M = P.size();
    vector<uint> prefix_min(M);
    for(uint i = 0; i < M; ++i)
    {
        prefix_min[i] = min_impact(S, P[i], Q[i]);
    }
    return prefix_min;
}

TEST(GenomicRangeQuery, Trivial)
{
	EXPECT_EQ(solution("CAGCCTA", vector<uint>{2, 5, 0}, vector<uint>{4, 5, 6}), (vector<uint>{2, 4, 1}));
}
