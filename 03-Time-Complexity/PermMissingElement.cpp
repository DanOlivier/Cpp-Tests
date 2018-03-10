#include "gtest/gtest.h"
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int solution(const vector<int>& A)
{
	ulong sum = 0;
	uint N = A.size();
	for(uint i = 0; i < N; i++)
	{
		sum += A[i];
	}
	ulong n = N+1;
	ulong expectedSum = n*(1 + n)/2;
	//cout << "expectedSum: " << expectedSum << endl;
	//cout << "sum:         " << sum << endl;
	//cout << "diff:        " << (expectedSum - sum) << endl;
	return expectedSum - sum;
}

int myrandom (int i) { return std::rand()%i; }

void printv(const vector<int>& A)
{
	for(int i: A)
	{
		cout << i << ", ";
	}
	cout << endl;
}

TEST(PermMissingElem, Trivial)
{
	srand ( unsigned ( time(0) ) );
  
	EXPECT_EQ(solution(vector<int>{ 2, 3, 1, 5 }), 4);
	EXPECT_EQ(solution(vector<int>{ 2, 3, 1, 5, 6, 9, 4, 10, 8, 11}), 7);
	EXPECT_EQ(solution(vector<int>{ 2, 3, 1, 5, 9, 7, 12, 4, 10, 8, 11}), 6);
	for(int i = 0; i < 10000; ++i)
	{
		vector<int> a(myrandom(100000)+1);
		iota(a.begin(), a.end(), 1);
		vector<int>::iterator it = a.begin() + myrandom(a.size());
		int saved = *it;
		a.erase(it);
		a.shrink_to_fit();
		std::random_shuffle( a.begin(), a.end() );
		//printv(a);
		//cout << "saved: " << saved << endl;

		EXPECT_EQ(solution(a), saved);
	}

}