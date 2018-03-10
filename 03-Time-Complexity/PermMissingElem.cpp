#include "gtest/gtest.h"
#include <cstdlib>      // std::rand, std::srand
#include <algorithm>
#include <numeric>

using namespace std;

int solution(int A[], int N)
{
	ulong sum = 0;
	for(int i = 0; i < N; i++)
	{
		sum += A[i];
	}
	ulong n = N+1;
	ulong expectedSum = n*(1 + n)/2;
	cout << "expectedSum: " << expectedSum << endl;
	cout << "sum:         " << sum << endl;
	return expectedSum - sum;
}

int solution(vector<int> &A)
{
	return solution(&A[0], A.size());
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
  
	{
		vector<int> a{ 2, 3, 1, 5 };
		EXPECT_EQ(solution(a), 4);
	}
	{
		vector<int> a{ 2, 3, 1, 5, 6, 9, 4, 10, 8, 11};
		EXPECT_EQ(solution(a), 7);
	}
	{
		vector<int> a{ 2, 3, 1, 5, 9, 7, 12, 4, 10, 8, 11};
		EXPECT_EQ(solution(a), 6);
	}
	{
		vector<int> a(10);
		iota(a.begin(), a.end(), 1);
		vector<int>::iterator it = a.begin() + myrandom(a.size());
		int saved = *it;
		a.erase(it);
		a.shrink_to_fit();
		std::random_shuffle( a.begin(), a.end() );
		//printv(a);
		cout << "saved: " << saved << endl;

		EXPECT_EQ(solution(a), saved);
	}

}