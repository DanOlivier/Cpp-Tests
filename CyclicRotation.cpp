#include "gtest/gtest.h"

#include <vector>
#include <sstream>

using namespace std;

vector<int> solution(vector<int> &A, uint K)
{
	if(K >= A.size())
	{
		stringstream os; 
		os << "Rotation factor (" << K << ") must be smaller than size of vector (" << A.size() << ")!";
		throw runtime_error(os.str());
	}
	vector<int> B(A.size());
	copy(A.end()-K, A.end(), B.begin());
	copy(A.begin(), A.end()-K, B.begin()+K);
	return B;
}

TEST(CyclicRotation, Trivial)
{
	{
		vector<int> a{ 9, 7 }, b{ 7, 9 };
		EXPECT_EQ(solution(a, 1), b);
	}
	{
		vector<int> a{ 9, 7 }, b{ 7, 9 };
		ASSERT_THROW(solution(a, 2), runtime_error);
	}
	{
		vector<int> e{ 9, 7, 6 }, f{ 6, 9, 7 };
		EXPECT_EQ(solution(e, 1), f);
	}
	{
		vector<int> g{ 9, 7, 6 }, h{ 7, 6, 9 };
		EXPECT_EQ(solution(g, 2), h);
	}
	{
		vector<int> k{ 3, 8, 9, 7, 6 }, l{ 9, 7, 6, 3, 8 };
		EXPECT_EQ(solution(k, 3), l);
	}
	{
		vector<int> k{ 3, 8, 9, 7, 6 }, l{ 8, 9, 7, 6, 3 };
		EXPECT_EQ(solution(k, 4), l);
	}}
