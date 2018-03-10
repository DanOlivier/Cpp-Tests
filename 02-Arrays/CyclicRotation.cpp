#include "gtest/gtest.h"

#include <vector>
#include <sstream>

using namespace std;

vector<int> solution(vector<int> &A, int K)
{
	// Need to truncate to not rotate over the size of the the vector?
	if(K > 0)
		K = K % A.size();
	if(K < 0)
		K = -(-K % A.size());
	if(K == 0)
		return A;

	vector<int> B(A.size());
	if(K < 0)
		K = A.size() + K;
	copy(A.end()-K, A.end(), B.begin());
	copy(A.begin(), A.end()-K, B.begin()+K);
	return B;
}

TEST(CyclicRotation, Trivial)
{
	{
		vector<int> a{ 9, 7 }, b{ 7, 9 };
		EXPECT_EQ(solution(a, 1), b);
		EXPECT_EQ(solution(a, 2), a);
		EXPECT_EQ(solution(a, 3), b);
	}
	{
		vector<int> 
			e{ 9, 7, 6 }, 
			f{ 6, 9, 7 }, 
			g{ 7, 6, 9 };
		EXPECT_EQ(solution(e, 1), f);
		EXPECT_EQ(solution(e, 2), g);
		EXPECT_EQ(solution(e, 3), e);
		EXPECT_EQ(solution(e, 4), f);
	}
	{
		vector<int> 
			a{ 3, 8, 9, 7, 6 }, 
			b{ 6, 3, 8, 9, 7 }, 
			c{ 7, 6, 3, 8, 9 }, 
			d{ 9, 7, 6, 3, 8 },
			e{ 8, 9, 7, 6, 3 };
		EXPECT_EQ(solution(a, 1), b);
		EXPECT_EQ(solution(a, 2), c);
		EXPECT_EQ(solution(a, 3), d);
		EXPECT_EQ(solution(a, 4), e);
		EXPECT_EQ(solution(a, 5), a);
		EXPECT_EQ(solution(a, 6), b);
	}
}

TEST(CyclicRotation, Negative)
{
	{
		vector<int> a{ 9, 7 }, b{ 7, 9 };
		EXPECT_EQ(solution(a, -1), b);
		EXPECT_EQ(solution(a, -2), a);
		EXPECT_EQ(solution(a, -3), b);
	}
	{
		vector<int> 
			e{ 9, 7, 6 }, 
			f{ 7, 6, 9 }, 
			g{ 6, 9, 7 };
		EXPECT_EQ(solution(e, -1), f);
		EXPECT_EQ(solution(e, -2), g);
		EXPECT_EQ(solution(e, -3), e);
		EXPECT_EQ(solution(e, -4), f);
	}
	{
		vector<int> 
			a{ 3, 8, 9, 7, 6 }, 
			b{ 8, 9, 7, 6, 3 }, 
			c{ 9, 7, 6, 3, 8 },
			d{ 7, 6, 3, 8, 9 },
			e{ 6, 3, 8, 9, 7 };
		EXPECT_EQ(solution(a, -1), b);
		EXPECT_EQ(solution(a, -2), c);
		EXPECT_EQ(solution(a, -3), d);
		EXPECT_EQ(solution(a, -4), e);
		EXPECT_EQ(solution(a, -5), a);
		EXPECT_EQ(solution(a, -6), b);
	}
}
