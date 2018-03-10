#include "gtest/gtest.h"

#include <array>
#include <string>
#include <set>
#include <unordered_set>
#include <cstdlib>      // std::rand, std::srand

#include <algorithm>
#include <random>

using namespace std;

const unsigned int N = 1000000000;

uint solution(vector<uint>& A)
{
	unordered_set<uint> paired;
	unordered_set<uint> unpaired;

	for(uint i = 0; i < A.size(); i++)
	{
		uint j = A[i];

		// We allow duplicates, i.e. multiple values beyond first pair,
		// so we are basically flagging odd numbers of occurrences of specific numbers
		unordered_set<uint>::iterator it = unpaired.find(j);
		if(it != unpaired.end())
		{
			paired.insert(j);
			unpaired.erase(it);
		}
		else
		{
			unordered_set<uint>::iterator it2 = paired.find(j);
			if(it2 != paired.end())
			{
				paired.erase(it2);
			}

			unpaired.insert(j);
		}
	}

	if(unpaired.size() == 0)
		throw runtime_error("No unpaired numbers found!");
	if(unpaired.size() > 1)
		throw runtime_error("Multiple unique values found!");
	return *unpaired.begin();
}

TEST(OddOccurrencesInArray, Trivial)
{
	printf("N: %u\n", N);

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

void validateForVectorSize(uint vs)
{
	if(!(vs % 2)) // make sure it's even
		throw runtime_error("Vector size expected to be odd");
	unordered_set<uint> s; // set of paired numbers
	while(s.size() < (vs/2+2))
		s.insert(myrandom(N));
	auto last = s.begin();
	uint extra = *last;
	s.erase(*last);
	last = s.begin();
	uint extra2 = *last;
	s.erase(*last);

	// populate the array
	vector<uint> arr;
	arr.reserve(vs);
	for(int i = 0; i < 2; ++i)
	{
		for(uint i: s)
		{
			arr.push_back(i);
		}
	}

	cout << "Testing for: " << vs/2 << " paired elements" << endl;
	EXPECT_THROW(solution(arr), runtime_error);

	random_device rd;
	mt19937 g(rd());
	shuffle(arr.begin(), arr.end(), g);

	vector<uint>::iterator it;
	if(arr.size() > 0)
	{
		it = arr.begin()+myrandom(arr.size());
		arr.insert(it, extra);
	}
	else
		arr.push_back(extra);

	cout << "Testing for: " << vs/2 << " paired elements + 1 unique value (" << extra << ")" << endl;
	EXPECT_EQ(solution(arr), extra);

	it = arr.begin()+myrandom(arr.size());
	arr.insert(it, extra2);

	cout << "Testing for: " << vs/2 << " paired elements + 2 unique value (" << extra << ")" << endl;
	EXPECT_THROW(solution(arr), runtime_error);
}

TEST(OddOccurrencesInArray, Randomized)
{
	srand ( unsigned ( time(0) ) );

	validateForVectorSize(1);
	validateForVectorSize(3);
	validateForVectorSize(5);

	for(uint j = 0; j < 100; ++j)
	{
		uint vs = myrandom(1000000); // random vector size
		if(!(vs % 2)) vs++; // make sure it's odd
		validateForVectorSize(vs);
	}
}
