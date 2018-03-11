#include "gtest/gtest.h"

#include <vector>

using namespace std;

int solution(const vector<int>& A)
{
	int eastbound = 0;
	int passing_sum = 0;
	vector<int>::const_reverse_iterator it = A.rbegin(), it2 = A.rend(); 
	for(; it != it2; ++it)
	{
		if(*it)
		{
			eastbound++;
		}
		else
		{
			passing_sum += eastbound;
			if(passing_sum >  1000000000)
				return -1;
		}
	}
	return passing_sum;
}

TEST(PassingCars, Trivial)
{
	EXPECT_EQ(solution(vector<int>{ 0, 1, 0, 1, 1}), 5);
	EXPECT_EQ(solution(vector<int>{ 0 }), 0);
	EXPECT_EQ(solution(vector<int>{ 0, 1 }), 1);
	EXPECT_EQ(solution(vector<int>{ 0, 1, 1 }), 2);
	EXPECT_EQ(solution(vector<int>{ 0, 1, 1, 0 }), 2);
}
