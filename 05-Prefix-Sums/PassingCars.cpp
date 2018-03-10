#include "gtest/gtest.h"

#include <vector>

using namespace std;

int solution(vector<int> &A)
{
	int counted_1 = 0;
	int passing_sum = 0;
	for(vector<int>::reverse_iterator it = A.rbegin(), it2 = A.rend(); it != it2; ++it)
	{
		if(*it)
		{
			counted_1++;
		}
		else
		{
			passing_sum += counted_1;
			if(passing_sum >  1000000000)
				return -1;
		}
	}
	return passing_sum;
}

TEST(PassingCars, Trivial)
{
	vector<int> A{ 0, 1, 0, 1, 1};
	EXPECT_EQ(solution(A), 5);

	A = { 0 };
	EXPECT_EQ(solution(A), 0);

	A = { 0,1 };
	EXPECT_EQ(solution(A), 1);

	A = { 0,1,1 };
	EXPECT_EQ(solution(A), 2);

	A = { 0,1,1,0 };
	EXPECT_EQ(solution(A), 2);
}
