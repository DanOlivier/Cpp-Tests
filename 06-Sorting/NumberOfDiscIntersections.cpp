#include <vector>
//#include <iostream>
//#include <iterator>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct IntersectionEvent
{
    IntersectionEvent(bool _open, long _x) : open(_open), x(_x) { }
    bool open;
    long x;
};

/*ostream_iterator<int> out_it (cout,", ");
ostream& operator<<(ostream& os, const IntersectionEvent& e)
{
    os << "(" << e.x << ", " << (e.open ? "1" : "-1") << ")";
    return os;
}
ostream_iterator<const IntersectionEvent&> out_it2 (cout,", ");
*/
int solution(const vector<int>& A)
{
    const uint N = A.size();
    //copy(A.begin(), A.end(), out_it ); cout << endl;

    typedef vector<IntersectionEvent> IntersectionSetType;
    IntersectionSetType intersections;
    for(uint i = 0; i < N; ++i)
    {
        int r = A[i];
        if(r < 0)
            throw runtime_error("Invalid negative radius");
        intersections.push_back(IntersectionEvent(true, long(i)-r));
        intersections.push_back(IntersectionEvent(false, long(i)+r));
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
        if(nbIntersections > 1E7)
            return -1;
    }
    //cout << "Result: " << nbIntersections << endl << endl;
    return nbIntersections;
}

#include <gtest/gtest.h>
#include <limits.h>

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

TEST(NumberOfDiscIntersections, Overflow)
{
    EXPECT_THROW(solution(vector<int>{-2, -3}), runtime_error);
    EXPECT_EQ(solution(vector<int>{INT_MAX, INT_MAX-1}), 1);
}
