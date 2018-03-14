#include <vector>
//#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

template <typename K>
class CountedMap
{
    std::unordered_map<K, uint> m;
public:
    CountedMap() {}
    void add(K i) { m[i]++; }
    void remove(K i) {
        unordered_map<int, uint>::iterator it = m.find(i);
        if(it != m.end())
        {
            it->second--;
            if(it->second < 1)
                m.erase(it);
        }
    }
    size_t size() { return m.size(); }
};

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
    
    CountedMap<int> S;

    uint min_days = N;
    uint start = 0;
    for(uint i = 0; i < N; i++)
    {
        if(i-start+1 > min_days) // we don't consider solutions larger than the current one
        {
            S.remove(A[start]); // sliding window remove from start
            start++;
        }
        S.add(A[i]);

        while(S.size() == sizeS) // The set is filled, and all destinations have been visited
        {
            min_days = min(min_days, (uint)i-start+1);
            if(min_days == sizeS)
                return sizeS; // optimal
            // shrink the window from the start
            S.remove(A[start]);
            start++;
        }
    }
    return min_days;
}
