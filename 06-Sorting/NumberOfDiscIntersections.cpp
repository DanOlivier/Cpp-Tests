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

struct CircleIntersection
{
    CircleIntersection(bool _open, int _x, Circle* _pCircle) :
        open(_open), x(_x), pCircle(_pCircle) { }
    bool open;
    int x;
    Circle* pCircle;
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
    typedef multiset<CircleIntersection, IntersectCompare> IntersectionSetType;
    IntersectionSetType intersections;
    for(uint i = 0; i < N; ++i)
    {
        int r = A[i];
        circles.push_back(Circle(i, r));
        intersections.insert(CircleIntersection(true, i-r, &circles[i]));
        intersections.insert(CircleIntersection(false, i-r, &circles[i]));
    }
    // sort(D.begin(), D.end(), [&](const pair<int,int>& a, const pair<int,int>& b){
    //     return a.first < b.first;
    // });

    // Travel along x-axis towards the right
    vector<Circle*> openCircles;
    for(auto& ci: intersections)
    {
        printf("Circle %p, is %s at x=%d\n", ci.pCircle, ci.open ? "open" : "closed", ci.x);
        if(ci.open)
        {
            for(auto oc: openCircles)
            {
                
            }
            openCircles.push_back(ci.pCircle);
        }
        else
        {
            vector<Circle*>::iterator it = find(openCircles.begin(), openCircles.end(), ci.pCircle);
            if(it != openCircles.end())
                openCircles.erase(it);
        }
    }
    cout << endl;
    return 0;
}

TEST(NumberOfDiscIntersections, Trivial)
{
    EXPECT_EQ(solution(vector<int>{0, 0}), 0);
    EXPECT_EQ(solution(vector<int>{0, 1}), 1);
    EXPECT_EQ(solution(vector<int>{1, 1}), 1);
    EXPECT_EQ(solution(vector<int>{1, 2}), 1);
    EXPECT_EQ(solution(vector<int>{1, 3}), 0);
    EXPECT_EQ(solution(vector<int>{2, 1}), 1);
    EXPECT_EQ(solution(vector<int>{2, 2}), 1);
    EXPECT_EQ(solution(vector<int>{1, 0, 1}), 1);
    EXPECT_EQ(solution(vector<int>{2, 0, 0, 0, 2}), 1);
    EXPECT_EQ(solution(vector<int>{2, 0, 0, 0, 0, 2}), 0);
    EXPECT_EQ(solution(vector<int>{1, 5, 2, 1, 4, 0}), 11);
}


