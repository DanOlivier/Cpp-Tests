#include "gtest/gtest.h"

#include <vector>
#include <string>
#include <limits.h>
#include <stdexcept>
#include <algorithm>
#include <iostream>

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
    uint N = S.size();
    vector<uint> prefix_A(N+1), suffix_A(N+1);
    vector<uint> prefix_C(N+1), suffix_C(N+1);
    vector<uint> prefix_G(N+1), suffix_G(N+1);
    vector<uint> prefix_T(N+1), suffix_T(N+1);
    uint countA = 0, countC = 0, countG = 0, countT = 0;
    for(uint i = 0; i < N; ++i)
    {
        const auto& c = S[i];
        switch(c)
        {
        case 'A': countA += 1; break;
        case 'C': countC += 1; break;
        case 'G': countG += 1; break;
        case 'T': countT += 1; break;
        default:
            throw runtime_error("Invalid nucleotide character");
        }
        prefix_A[i+1] += countA;
        prefix_C[i+1] += countC;
        prefix_G[i+1] += countG;
        prefix_T[i+1] += countT;
    }
    countA = 0, countC = 0, countG = 0, countT = 0;
    for(uint i = N-1; ; --i)
    {
        const auto& c = S[i];
        switch(c)
        {
        case 'A': countA += 1; break;
        case 'C': countC += 1; break;
        case 'G': countG += 1; break;
        case 'T': countT += 1; break;
        default:
            throw runtime_error("Invalid nucleotide character");
        }
        suffix_A[i] = countA;
        suffix_C[i] = countC;
        suffix_G[i] = countG;
        suffix_T[i] = countT;
        if(i == 0) break;
    }
    //ostream_iterator<uint> out_it (cout,", ");
    //copy( prefix_A.begin(), prefix_A.end(), out_it ); cout << endl;
    //copy( suffix_A.begin(), suffix_A.end(), out_it ); cout << endl;
    //copy( prefix_C.begin(), prefix_C.end(), out_it ); cout << endl;
    //copy( suffix_C.begin(), suffix_C.end(), out_it ); cout << endl;
    //copy( prefix_G.begin(), prefix_G.end(), out_it ); cout << endl;
    //copy( suffix_G.begin(), suffix_G.end(), out_it ); cout << endl;
    //copy( prefix_T.begin(), prefix_T.end(), out_it ); cout << endl;
    //copy( suffix_T.begin(), suffix_T.end(), out_it ); cout << endl;

    uint M = P.size();
    vector<uint> impact_min(M);
    for(uint i = 0; i < M; ++i)
    {
        uint p = P[i], q = Q[i]+1;
        //cout << "P[i]: " << P[i] << ", Q[i]: " << Q[i] << endl;
        //cout << "p: " << p << ", q: " << q << endl;
        //cout << "prefix_A[q]: " << prefix_A[q] << ", prefix_A[p]: " << prefix_A[p] << ", diff:" << prefix_A[q] - prefix_A[p] << endl;
        //cout << "prefix_C[q]: " << prefix_C[q] << ", prefix_C[p]: " << prefix_C[p] << ", diff:" << prefix_C[q] - prefix_C[p] << endl;
        //cout << "prefix_G[q]: " << prefix_G[q] << ", prefix_G[p]: " << prefix_G[p] << ", diff:" << prefix_G[q] - prefix_G[p] << endl;
        //cout << "prefix_T[q]: " << prefix_T[q] << ", prefix_T[p]: " << prefix_T[p] << ", diff:" << prefix_T[q] - prefix_T[p] << endl;
        if((prefix_A[q] - prefix_A[p]) > 0)
        {
            impact_min[i] = 1;
            continue;
        }
        if((prefix_C[q] - prefix_C[p]) > 0)
        {
            impact_min[i] = 2;
            continue;
        }
        if((prefix_G[q] - prefix_G[p]) > 0)
        {
            impact_min[i] = 3;
            continue;
        }
        if((prefix_T[q] - prefix_T[p]) > 0)
        {
            impact_min[i] = 4;
            continue;
        }
        throw runtime_error("Invalid nucleotide character");
    }
    return impact_min;
}

TEST(GenomicRangeQuery, Trivial)
{
    EXPECT_EQ(solution("A", vector<uint>{0}, vector<uint>{0}), (vector<uint>{1}));
    EXPECT_EQ(solution("AC", vector<uint>{0}, vector<uint>{1}), (vector<uint>{1}));
    EXPECT_EQ(solution("AC", vector<uint>{1}, vector<uint>{1}), (vector<uint>{2}));
    EXPECT_EQ(solution("CAGCCTA", vector<uint>{2, 5, 0}, vector<uint>{4, 5, 6}), (vector<uint>{2, 4, 1}));
    EXPECT_EQ(solution("CAGCGGGAGGGGGGGGGGGGCTA", vector<uint>{2, 5, 0}, vector<uint>{4, 5, 12}), (vector<uint>{2, 3, 1}));
}
