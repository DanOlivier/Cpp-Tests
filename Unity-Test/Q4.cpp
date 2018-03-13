#include <vector>
#include <set>
#include <deque>
//#include <algorithm>
#include <unordered_set>

using namespace std;

int solution(const vector<int> &A)
{
    uint N = A.size();
    auto f = [&A]() -> uint {
        set<int> S1;
        for(auto a: A)
        {
            S1.insert(a);
        }
        return S1.size(); // number of unique elements
    };
    uint sizeS = f();
    
    unordered_set<int> S; // value to index
    deque<int> V;

    uint min_days = N;
    uint start = 0;
    for(uint i = 0; i < N; i++)
    {
        V.push_front(A[i]);
        S.insert(A[i]);
redo:
        if(S.size() == sizeS) // The set is filled, and all destinations have been visited
        {
            min_days = min(min_days, (uint)V.size());
            V.pop_back();
            S.clear();
            for(auto a: V) { S.insert(a); }
            start++;
            goto redo;
        }
    }
    return min_days;
}
