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

struct IntersectionEvent
{
    IntersectionEvent(bool _open, int _x, uint _pCircle) :
        open(_open), x(_x), iCircle(_pCircle) { }
    bool open;
    int x;
    uint iCircle;
};

ostream_iterator<int> out_it (cout,", ");
ostream& operator<<(ostream& os, const IntersectionEvent& e)
{
    os << "(" << e.x << ", " << (e.open ? "1" : "-1") << ")";
    return os;
}
ostream_iterator<const IntersectionEvent&> out_it2 (cout,", ");

int solution(const vector<int>& A)
{
    const uint N = A.size();
    //copy(A.begin(), A.end(), out_it ); cout << endl;

    typedef vector<IntersectionEvent> IntersectionSetType;
    IntersectionSetType intersections;
    for(uint i = 0; i < N; ++i)
    {
        int r = A[i];
        intersections.push_back(IntersectionEvent(true, i-r, i));
        intersections.push_back(IntersectionEvent(false, i+r, i));
    }
    sort(intersections.begin(), intersections.end(), [&](const IntersectionEvent& a, const IntersectionEvent& b) {
        if(a.x == b.x)
            return a.open > b.open;
        return a.x < b.x;
    });
    //copy(intersections.begin(), intersections.end(), out_it2 ); cout << endl;

    // Travel along x-axis towards the right
    uint openCircles = 0;
    int nbIntersections = 0;
    for(auto& i: intersections)
    {
        if(i.open)
        {
            nbIntersections += openCircles;
            openCircles += 1;
        }
        else 
        {
            openCircles -= 1;
        }
        if(nbIntersections >= 1E6)
            return -1;
    }
    //cout << "Result: " << nbIntersections << endl << endl;
    return nbIntersections;
}

TEST(NumberOfDiscIntersections, Trivial)
{
    EXPECT_EQ(solution(vector<int>{}), 0);
    EXPECT_EQ(solution(vector<int>{1,0,0,3}), 4);

    EXPECT_EQ(solution(vector<int>{0, 0}), 0);
    EXPECT_EQ(solution(vector<int>{0, 1}), 1);
    EXPECT_EQ(solution(vector<int>{1, 1}), 1);
    EXPECT_EQ(solution(vector<int>{1, 2}), 1);
    EXPECT_EQ(solution(vector<int>{1, 3}), 1);
    EXPECT_EQ(solution(vector<int>{2, 1}), 1);
    EXPECT_EQ(solution(vector<int>{2, 2}), 1);
    EXPECT_EQ(solution(vector<int>{1, 0, 1}), 3);
    EXPECT_EQ(solution(vector<int>{2, 0, 0, 2}), 5);
    EXPECT_EQ(solution(vector<int>{2, 0, 0, 0, 2}), 5);
    EXPECT_EQ(solution(vector<int>{2, 0, 0, 0, 0, 2}), 4);
    EXPECT_EQ(solution(vector<int>{1, 5, 2, 1, 4, 0}), 11);
}


