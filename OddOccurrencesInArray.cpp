#include "gtest/gtest.h"

#include <array>
#include <string>
#include <set>
#include <cstdlib>      // std::rand, std::srand

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


	static string print_headline()
	{
		constexpr uint nb_bits = sizeof(T)*8;
		string result;
		for(uint i = 0; i < MAX_VAL; i++)
		{
			uint j = i % nb_bits;
			result += hex(j);
			if(j+1 == nb_bits)
				result += '|';
		}
		return result;
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

	T operator[](uint i) const
	{
		return m_array[i];
	}
	T& operator[](uint i)
	{
		return m_array[i];
	}
};

template<typename T, uint MAX_VAL>
BitField<T, MAX_VAL> operator&(const BitField<T, MAX_VAL>& a, const BitField<T, MAX_VAL>& b)
{
	constexpr uint N = div_up(MAX_VAL, sizeof(char)*8);
	BitField<T, MAX_VAL> c;
	for(uint i = 0; i < N; i++)
	{
		c[i] = a[i] & b[i];
	}
	return c;
}

template<typename T, uint MAX_VAL>
BitField<T, MAX_VAL> operator~(const BitField<T, MAX_VAL>& a)
{
	constexpr uint N = div_up(MAX_VAL, sizeof(char)*8);
	BitField<T, MAX_VAL> c;
	for(uint i = 0; i < N; i++)
	{
		c[i] = ~a[i];
	}
	return c;
}

template<typename T, uint MAX_VAL>
BitField<T, MAX_VAL> countOccurrences(vector<int>& A)
{
	//static_assert(N >= sizeof(int));
	BitField<T, MAX_VAL> paired;
	BitField<T, MAX_VAL> occurred;
	for(uint i = 0; i < A.size(); i++)
	{
		int j = A[i];
		/*if(j >= MAX_VAL)
			throw runtime_error("Value exceeds maximum allowed!");*/

		if(occurred.get_bit(j))
			paired.set_bit(j);
		else
			occurred.set_bit(j);
	}

	//cout << "occurred: " << occurred.print_array() << "\n";
	//cout << "paired  : " << paired.print_array()   << "\n";
	
	BitField<T, MAX_VAL> unpaired = occurred & ~paired;
	//cout << "unpaired: " << unpaired.print_array() << "\n";
	//cout << "\n";

	return unpaired;
}

const int MAX_VAL2 = 1000001;

uint solution(vector<int>& A)
{
	BitField<uint64_t, MAX_VAL2> unpaired = countOccurrences<uint64_t, MAX_VAL2>(A);
	bool found = false;
	uint val = 0;
	for(uint i = 0; i < MAX_VAL2; i++)
		if(unpaired.get_bit(i))
		{
			if(found)
				return 0; //throw runtime_error("Multiple unique values found!");

			val = i;
			found = true;
		}
	if(!found)
		return 0; //throw runtime_error("No unpaired numbers found!");
	return val;
}

int myrandom (int i) { return std::rand()%i; }

TEST(OddOccurrencesInArray, Trivial)
{
	srand ( unsigned ( time(0) ) );

	printf("MAX_VAL: %d\n", MAX_VAL2);
	//cout << "          " << BitField<uint64_t, MAX_VAL2>::print_headline() << endl;


	/*array<int, 7> A{9, 3, 9, 3, 9, 7, 9};
	EXPECT_EQ(solution(A.data(), A.size()), 7);

	array<int, 7> B{9, 3, 9, 3, 9, 10, 10}; // no unpaired numbers
	ASSERT_THROW(solution(B.data(), B.size()), runtime_error);

	array<int, 8> C{9, 3, 9, 3, 9, 10, 10, 0};
	EXPECT_EQ(solution(C.data(), C.size()), 0);

	array<int, 8> D{9, 3, 9, 3, 9, 49, 11, 11 };
	EXPECT_EQ(solution(D.data(), D.size()), 49);

	array<int, 8> E{9, 3, 9, 3, 37, 49, 11, 11 }; // multiple unique values
	EXPECT_THROW(solution(E.data(), E.size()), runtime_error);
*/
	for(int j=0; j<100;++j)
	{
		vector<int> vec_sizes{1000000};
		for(int vs: vec_sizes)
		{
			vector<int> a(vs+1);
			set<int> s;
			while(s.size() < vs/2)
				s.insert(myrandom(MAX_VAL2));
			for(int i: s)
			{
				a.push_back(i);
				a.push_back(i);
			}

			int other = 0;
			/*if(myrandom(100) >= 90)
			{
				other = myrandom(MAX_VAL2);
				a.push_back(other);
			}
			else*/
			{
				pair<set<int>::iterator,bool> ret;
				while(s.size() < (vs/2+1))
					ret = s.insert(myrandom(MAX_VAL2));
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
