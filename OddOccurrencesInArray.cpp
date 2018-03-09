#include "gtest/gtest.h"

#include <array>
#include <string>
#include <set>
#include <cstdlib>      // std::rand, std::srand

#include <bitset>

using namespace std;

const unsigned int N = 1000000000;

uint solution(vector<uint>& A)
{
	bitset<N> paired;
	bitset<N> occurred;
	for(uint i = 0; i < A.size(); i++)
	{
		uint j = A[i];

		// We allow duplicates, i.e. multiple values beyond first pair,
		// so we are basically flagging odd numbers of occurrences of specific numbers
		if(occurred[j])
		{
			paired.set(j);
			occurred.reset(j);
		}
		else
		{
			occurred.set(j);
			paired.reset(j);
		}
	}

	bitset<N> unpaired = occurred & ~paired;
	bool found = false;
	uint val = 0;
	for(uint i = 0; i < N; i++)
	{
		if(unpaired[i])
		{
			if(found)
				throw runtime_error("Multiple unique values found!");

			val = i;
			found = true;
		}
	}
	if(!found)
		throw runtime_error("No unpaired numbers found!");
	return val;
}

TEST(OddOccurrencesInArray, Trivial)
{
	printf("N: %u, size: %lu\n", N, sizeof(bitset<N>));

	vector<uint> A{9, 3, 9, 3, 9, 7, 9};
	EXPECT_EQ(solution(A), 7);

	vector<uint> B{9, 3, 9, 3, 10, 10}; // no unpaired numbers
	ASSERT_THROW(solution(B), runtime_error);

	vector<uint> C{9, 3, 9, 3, 9, 10, 10, 0};
	EXPECT_THROW(solution(C), runtime_error); // multiple unique values

	vector<uint> D{9, 3, 9, 3, 49, 11, 11 };
	EXPECT_EQ(solution(D), 49);

	vector<uint> E{9, 3, 9, 3, 37, 49, 11, 11 }; // multiple unique values
	EXPECT_THROW(solution(E), runtime_error);
}

uint myrandom (uint i) { return std::rand()%i; }

TEST(OddOccurrencesInArray, Randomized)
{
	srand ( unsigned ( time(0) ) );
	for(uint j=0; j<100;++j)
	{
		vector<uint> vec_sizes{1000000};
		for(uint vs: vec_sizes)
		{
			vector<uint> a(vs+1);
			set<uint> s;
			while(s.size() < vs/2)
				s.insert(myrandom(N));
			for(uint i: s)
			{
				a.push_back(i);
				a.push_back(i);
			}

			uint other = 0;
			/*if(myrandom(100) >= 90)
			{
				other = myrandom(N);
				a.push_back(other);
			}
			else*/
			{
				pair<set<uint>::iterator,bool> ret;
				while(s.size() < (vs/2+1))
					ret = s.insert(myrandom(N));
				other = *ret.first;
				a.push_back(other);
			}

			std::random_shuffle( a.begin(), a.end() );
			std::random_shuffle( a.begin(), a.end() );

			cout << "Testing for: " << vs << " elements + 1 unique value (" << other << ")" << endl;
			EXPECT_EQ(solution(a), other);
		}
	}
}
