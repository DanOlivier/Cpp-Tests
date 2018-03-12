#include <gtest/gtest.h>

#include <vector>
#include <map>
#include <list>
#include <stack>
#include <iostream>

using namespace std;

struct Circle {
    Circle(int _x, int _r) : x(_x), r(_r) {}
    int x;
    int r;
};

enum class OpenCloseBoth { OPEN, CLOSE, BOTH };
const char* print(OpenCloseBoth c)
{
    switch(c)
    {
    case OpenCloseBoth::OPEN:  return "OPEN";
    case OpenCloseBoth::CLOSE: return "CLOSE";
    case OpenCloseBoth::BOTH:  return "BOTH";
    }
    return 0;
}

struct CircleIntersection
{
    CircleIntersection(OpenCloseBoth _open, int _x, uint _pCircle) :
        open(_open), x(_x), iCircle(_pCircle) { }
    OpenCloseBoth open;
    int x;
    uint iCircle;
};

struct IntersectCompare {
    bool operator()(const CircleIntersection& a, const CircleIntersection& b)
    {
        //if(a.x == b.x)
        //    return a.open < b.open;
        return a.x < b.x;
    }
};

ostream_iterator<int> out_it (cout,", ");

int solution(const vector<int>& A)
{
    const uint N = A.size();
    copy(A.begin(), A.end(), out_it ); cout << endl;

    vector<Circle> circles; circles.reserve(N);
    typedef map<int, vector<CircleIntersection>> IntersectionSetType;
    IntersectionSetType intersections;
    for(uint i = 0; i < N; ++i)
    {
        int r = A[i];
        circles.push_back(Circle(i, r));
        if(r == 0)
        {
            intersections[i].push_back(CircleIntersection(OpenCloseBoth::BOTH, i-r, i));
            continue;
        }
        
        intersections[i-r].push_back(CircleIntersection(OpenCloseBoth::OPEN, i-r, i));
        intersections[i+r].push_back(CircleIntersection(OpenCloseBoth::CLOSE, i+r, i));
    }

    // Travel along x-axis towards the right
    vector<uint> openCircles;
    int nbIntersections = 0;
    for(auto& i: intersections)
    {
        int x = i.first;
        printf("----- Processing %lu intersections at x=%d\n", i.second.size(), x);
        for(auto& ci: i.second)
        {
            Circle& c2 = circles[ci.iCircle];
            printf("Circle %d  [x=%d, r=%d], is %s at x=%d\n", ci.iCircle, c2.x, c2.r, print(ci.open), ci.x);
            if(ci.open == OpenCloseBoth::OPEN || ci.open == OpenCloseBoth::BOTH)
            {
                openCircles.push_back(ci.iCircle);
            }
        }

        for(auto& ci: i.second)
        {
            if(ci.open == OpenCloseBoth::OPEN)
                continue;

            for(auto& oc: openCircles)
            {
                if(oc == ci.iCircle)
                {
                    continue;
                }
                Circle& c = circles[oc];
                Circle& c2 = circles[ci.iCircle];
                if(c.x - c.r >= (x - 2*c2.r))
                {
                    printf("==> Circle %d [x=%d, r=%d], intersects with %d [x=%d, r=%d] at x=%d\n", 
                        ci.iCircle, c2.x, c2.r, 
                        oc, c.x, c.r, ci.x);
                    nbIntersections++;
                }
            }
        }
        for(auto& ci: i.second)
        {
            if(ci.open == OpenCloseBoth::OPEN)
                continue;
            
            vector<uint>::iterator it = openCircles.begin(), 
                it2 = openCircles.end();
            for(; it != it2; ++it)
            {
                auto& oc = *it;
                if(oc == ci.iCircle)
                {
                    it = openCircles.erase(it);
                    break;
                }
            }
        }
    }
    EXPECT_EQ(openCircles.size(), 0);
    cout << "Result: " << nbIntersections << endl << endl;
    return nbIntersections;
}

TEST(NumberOfDiscIntersections, Trivial)
{
    //EXPECT_EQ(solution(vector<int>{0, 0}), 0);
    //EXPECT_EQ(solution(vector<int>{0, 1}), 1);
    //EXPECT_EQ(solution(vector<int>{1, 1}), 1);
    //EXPECT_EQ(solution(vector<int>{1, 2}), 1);
    //EXPECT_EQ(solution(vector<int>{1, 3}), 0);
    //EXPECT_EQ(solution(vector<int>{2, 1}), 1);
    //EXPECT_EQ(solution(vector<int>{2, 2}), 1);
    //EXPECT_EQ(solution(vector<int>{1, 0, 1}), 3);
    //EXPECT_EQ(solution(vector<int>{2, 0, 0, 0, 2}), 3);
    //EXPECT_EQ(solution(vector<int>{2, 0, 0, 0, 0, 2}), 2);
    EXPECT_EQ(solution(vector<int>{1, 5, 2, 1, 4, 0}), 11);
}


