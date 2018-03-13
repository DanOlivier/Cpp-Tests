#include <array>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

constexpr uint div_up(uint n, uint d) {
    return (n / d) + ((n % d) && 1);
} //i.e. +1 iff (not exact int && positive result)

template<typename T, uint MAX_VAL>
class BitField
{
	static constexpr uint N = div_up(MAX_VAL, sizeof(char)*8);
	array<T, N> m_array{0};

	static char hex(uint i) {
		const uint j = i % 16;
		if(j < 10)
			return '0' + j;
		return 'a' + j - 10;
	}
public:
	bool get_bit(uint i) const
	{
		constexpr uint nb_bits = sizeof(T)*8;
		if(i >= MAX_VAL)
			throw runtime_error("Value exceeds maximum allowed!");
		uint j = i / nb_bits;
		uint r = i % nb_bits;
		T t = (T(1) << r);
		return m_array[j] & t;
	}

	bool set_bit(uint i)
	{
		constexpr uint nb_bits = sizeof(T)*8;
		if(i >= MAX_VAL)
			throw runtime_error("Value exceeds maximum allowed!");
		uint j = i / nb_bits;
		uint r = i % nb_bits;
		T t = (T(1) << r);
		bool old = m_array[j] & t;
		m_array[j] |= t;
		return old;
	}

	bool clear_bit(uint i)
	{
		constexpr uint nb_bits = sizeof(T)*8;
		if(i >= MAX_VAL)
			throw runtime_error("Value exceeds maximum allowed!");
		uint j = i / nb_bits;
		uint r = i % nb_bits;
		T t = (T(1) << r);
		bool old = m_array[j] & t;
		m_array[j] &= ~t;
		return old;
	}

	string print_array()
	{
		constexpr uint nb_bits = sizeof(T)*8;
		string result;
		for(uint i = 0; i < MAX_VAL; i++)
		{
			uint j = i % nb_bits;
			result += get_bit(i) ? '1' : '0';
			if(j+1 == nb_bits)
				result += '|';
		}
		return result;
	}
};


const int MAX_VAL2 = 101;
int solution(const vector<int> &A)
{
	BitField<uint64_t, MAX_VAL2> occurred;
	for(uint i = 0; i < A.size(); i++)
	{
		int j = A[i];
		if(j > A.size())
			return 0;
		if(occurred.set_bit(j))
		    return 0;
	}
	cout << "occurred: " << occurred.print_array() << endl;
	for(uint i = 1; i < A.size()+1; i++)
	{
	    if(!occurred.get_bit(i))
	    {
	        return 0;
	    }
	}
	return 1;
}

/*int solution(vector<int> &T)
{
	int N = T.size();
	int k, x, y, z;
	for (k = 0, x = k-1, z = 0; 
		(k < N) && (T[k] <= N) && 
		((x+1) == k) && (z < N);
		++k)
	{
		for (x = k; 
			(T[x] > 0) && (T[x] <= N); 
			y = T[x], T[x] = 0, x = y-1, ++z)
			;
	}
	return (z == N ? 1 : 0);
}*/

#include "gtest/gtest.h"

TEST(isPermuation, Trivial)
{
	EXPECT_EQ(solution(vector<int>{1}), 1);
	EXPECT_EQ(solution(vector<int>{1,3}), 0);
	EXPECT_EQ(solution(vector<int>{1,2}), 1);
	EXPECT_EQ(solution(vector<int>{1,3,2,4}), 1);
	EXPECT_EQ(solution(vector<int>{9,8,7,6,5,4,3,2}), 0);
	{
		vector<int> A{
			 1, 2, 3, 4, 5, 6, 7, 8, 9,10,
			11,12,13,14,15,16,17,18,19,20,
			21,22,23,24,25,26,27,28,29,30,
			31,32,33,34,35,36,37,38,39,40,
			41,42,43,44,45,46,47,48,49,50,
			51,52,53,54,55,56,57,58,59,60,
			61,62,63,64,65,66,67,68,69,70,
			71,72,73,74,75,76,77,78,79,80,
			81,82,83,84,85,86,87,88,89,90,
			91,92,93,94,95,96,97,98,   100
		};
		EXPECT_EQ(solution(A), 0);
	}
	{
		vector<int> A{
			 1, 2, 3, 4, 5, 6, 7, 8, 9,10,
			11,12,13,14,15,16,17,18,19,20,
			21,22,23,24,25,26,27,28,29,30,
			31,32,33,34,35,36,37,38,39,40,
			41,42,43,44,45,46,47,48,49,50,
			51,52,53,54,55,56,57,58,59,60,
			61,62,63,64,65,66,67,68,69,70,
			71,72,73,74,75,76,77,78,79,80,
			81,82,83,84,85,86,87,88,89,90,
			91,92,93,94,95,96,97,98,99,100
		};
		EXPECT_EQ(solution(A), 1);
	}
}
