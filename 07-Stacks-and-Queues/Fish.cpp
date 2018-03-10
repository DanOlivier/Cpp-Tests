#include "gtest/gtest.h"

#include <vector>
#include <stack>
#include <bitset>

#include <cstdlib>      // std::rand, std::srand
#include <random>

using namespace std;

struct Fish { int size; bool downstream; };

pair<bool,Fish*> fight(Fish& f1, Fish& f2)
{
    if(f1.downstream && !f2.downstream)
    {
        if(f1.size >= f2.size)
        {
            return make_pair(true, &f1);
        }
        return make_pair(true, &f2);
    }
    return make_pair(false,(Fish*)0);
}

int solution(vector<int> &A, vector<int> &B)
{
    if(A.size() != B.size())
        return -1;
    if(A.size() > 100000 || B.size() > 100000)
        return -1;

    stack<Fish> fish;
    for(vector<int>::iterator 
        it = A.begin(), it2 = A.end(),
        it3 = B.begin();
        it != it2; ++it, ++it3)
    {
        Fish f1{.size = *it, .downstream = *it3};
        if(fish.empty())
        {
            fish.push(f1);
            continue;
        }
resume:
        Fish& f2 = fish.top();
        pair<bool,Fish*> result = fight(f2, f1);
        if(!result.first)
        {
            fish.push(f1);
            continue;
        }
        if(result.second == &f2)
            continue; // new fish f1 dies
        f2 = f1; // f2 dies, f1 takes its place
        // unroll the stack looking for fish to eat
        if(fish.size() >= 2)
        {
            f1 = fish.top();
            fish.pop();
            goto resume;
        }
    }
    //cout << "survivors: "; for(auto f: fish) { cout << f.size << ", "; }; cout << endl;
    return fish.size();
}

int myrandom (int i) { return rand()%i; }

template< size_t N>
bitset<N> random_bitset(double p = 0.5)
{
    bitset<N> bits;
    random_device rd;
    mt19937 gen( rd());
    bernoulli_distribution d( p);

    for( int n = 0; n < N; ++n) {
        bits[n] = d(gen);
    }

    return bits;
}

TEST(Fish, Trivial)
{
    {
        vector<int> A{4};
        vector<int> B{0};
        EXPECT_EQ(solution(A, B), 1);
        B[0] = 1;       
        EXPECT_EQ(solution(A, B), 1);       
    }
    {
        vector<int> A{4,3};
        vector<int> B{0,1};
        EXPECT_EQ(solution(A, B), 2);       
    }
    {
        vector<int> A{4,3};
        vector<int> B{1,0};
        EXPECT_EQ(solution(A, B), 1);       
    }
    {
        vector<int> A{4,3,5};
        vector<int> B{1,0,0};
        EXPECT_EQ(solution(A, B), 1);       
    }
    {
        vector<int> A{4,3,5};
        vector<int> B{0,1,1};
        EXPECT_EQ(solution(A, B), 3);       
    }
    {
        vector<int> A{4,3,2,1,5};
        vector<int> B{0,1,0,0,0};
        EXPECT_EQ(solution(A, B), 2);       
    }
    {
        vector<int> A{9,4,3,2,1,5};
        vector<int> B{1,0,1,0,0,0};
        EXPECT_EQ(solution(A, B), 1);       
    }
    {
        vector<int> A{6,7,8,9,4,3,2,1,5};
        vector<int> B{1,1,1,1,0,1,0,0,0};
        EXPECT_EQ(solution(A, B), 4);       
    }

    {
        // all except one fish flowing in the same direction
        vector<int> A{1,2,3,4,5,6,7,8,9,10};
        vector<int> B{1,1,1,1,1,1,1,1,1,0};
        EXPECT_EQ(solution(A, B), 1);       
    }
    {
        // all except one fish flowing in the same direction
        vector<int> A{10,9,8,7,6,5,4,3,2,1};
        vector<int> B{ 0,0,0,0,0,0,0,0,0,1};
        //EXPECT_EQ(solution(A, B), 10);       
    }

    {
        constexpr int MAX_VAL = 1000000000;
        //for(int j=0; j<100;++j)
        {
            // fish of various unique sizes
            vector<int> vec_sizes{10, 100, 1000, 10000, 100000};
            for(int vs: vec_sizes)
            {
                vector<int> a(vs);
                vector<int> b(vs);
                set<int> s;
                while(s.size() < vs)
                    s.insert(myrandom(MAX_VAL));
                bitset<100000> dir = random_bitset<100000>();
                int j = 0;
                for(int i: s)
                {
                    a.push_back(i);
                    b.push_back(dir[j++]);
                }
                solution(a, b);       
            }
        }
    }
}


