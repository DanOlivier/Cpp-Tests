#include "gtest/gtest.h"

#include <exception>
#include <cstdarg>
//#include <cmath>
#include <sstream>

using namespace std;

string string_format(const string &fmt, ...) {
    vector<char> str(100,'\0');
    va_list ap;
    while (1) {
        va_start(ap, fmt);
        auto n = vsnprintf(str.data(), str.size(), fmt.c_str(), ap);
        va_end(ap);
        if ((n > -1) && (size_t(n) < str.size())) {
            return str.data();
        }
        if (n > -1)
            str.resize( n + 1 );
        else
            str.resize( str.size() * 2);
    }
    return str.data();
}

template<typename T = int>
string convert_int_to_binary(T n)
{
	if(n < 0)
	{
		// %d must change according to int type...
		stringstream os;
		os << n;
		throw runtime_error("convert_int_to_binary doesn't handle negative numbers: " + os.str());
	}

	string result;
	//std::div_t dv;
	while(n > 0)
	{
		T rem = n % 2; 
		n /= 2; 
		result = (rem ? '1' : '0') + result;
	}
	return result;
}

template<typename T = int>
T convert_to_int(const string& bin_str)
{
	if(bin_str.length() > 8*sizeof(T))
	{
		throw runtime_error(string_format("String is too long (%d): %s", bin_str.length(), bin_str));
	}
	T result = 0;
	for(int i = bin_str.size()-1, j = 0; i >= 0; i--, j++)
	{
		switch(bin_str[i])
		{
		case '0':
			continue;
		case '1':
			result += (1 << j);
			break;
		default:
			throw runtime_error("String is not a binary number: " + bin_str);
		}
	}
	return result;
}

int solution(const string& N)
{
	string::const_iterator last_0 = N.end();
	int longest = 0;
	int current_longest = 0;
	for(string::const_iterator it = N.begin(), it2 = N.end();
		it != it2; it++)
	{
		switch(*it)
		{
		case '0':
			if(it - last_0 > current_longest)
				current_longest++;
			continue;
		case '1':
			last_0 = it;
			longest = std::max(current_longest, longest); 
			break;
		default:
			throw runtime_error("String is not a binary number: " + N);
		}
	}
	return longest;
}

/*template<typename T = int>
int solution(T N)
{
	string bin_str = convert_int_to_binary<T>(N);
	return solution(bin_str);
}*/

int solution(int N)
{
	int last_1 = sizeof(N)*8;
	int longest = 0;
	int current_longest = 0;
	for(int i = 0; i < int(sizeof(N)*8); i++)
	{
		bool b = (N & 1 << i);
		if(b)
		{
			int dist = i - last_1 - 1;
			if(dist > 0 && dist > current_longest)
			{
				current_longest = dist;
				longest = std::max(current_longest, longest); 
			}
			last_1 = i;
		}
	}
	return longest;
}

TEST(StringConvert, Trivial)
{
	EXPECT_EQ(convert_to_int("1001"), 9);
	EXPECT_EQ(convert_to_int("10001"), 17);
	EXPECT_EQ(convert_to_int("100001"), 33);
	EXPECT_EQ(convert_to_int("1000001"), 65);
	ASSERT_THROW(convert_to_int("888888888888810001"), runtime_error);
	ASSERT_THROW(convert_to_int("a"), runtime_error);
	ASSERT_THROW(convert_to_int("000000013e"), runtime_error);

	EXPECT_EQ(convert_int_to_binary(9), "1001");
	EXPECT_EQ(convert_int_to_binary(17), "10001");
	EXPECT_EQ(convert_int_to_binary(33), "100001");
	EXPECT_EQ(convert_int_to_binary(65), "1000001");
}

TEST(BasicTest, Trivial)
{
	EXPECT_EQ(solution(0b1001), 2);
	EXPECT_EQ(solution(0b10001), 3);
	EXPECT_EQ(solution(0b1000100001), 4);
	EXPECT_EQ(solution(0b10001000001), 5);
	EXPECT_EQ(solution(0b10001000001), 5);

	EXPECT_EQ(solution(0b1), 0);
	EXPECT_EQ(solution(0b11), 0);
	EXPECT_EQ(solution(0b111), 0);
	EXPECT_EQ(solution(0b101), 1);
	EXPECT_EQ(solution(0b1001), 2);
	EXPECT_EQ(solution(0b11110), 0);
	EXPECT_EQ(solution(0b1101100), 1);
	EXPECT_EQ(solution(0b1), 0);


	EXPECT_EQ(solution(0b1001), 2);
	EXPECT_EQ(solution(0b10001), 3);
	EXPECT_EQ(solution(0b1000100001), 4);
	EXPECT_EQ(solution(0b10001000001), 5);
	EXPECT_EQ(solution(0b10001000001), 5);
	EXPECT_EQ(solution(0b1000100000001), 7);
	EXPECT_EQ(solution(0b100010000000001), 9);
	EXPECT_EQ(solution(0b100010000000000), 3);
	
	// longest possible int ()
	EXPECT_EQ(solution( int(0b00001000000000001001111111111111)), 11);
	EXPECT_EQ(solution(uint(0b10001000000000001001111111111111)), 11);
	EXPECT_EQ(solution( int(0b00000000000000000000000000000000)), 0);

	EXPECT_EQ(solution( int(0b01000000000000000000000000000001)), 29);
	EXPECT_EQ(solution(uint(0b00000000000000000000000000000000)), 0);
	EXPECT_EQ(solution(uint(0b10000000000000000000000000000001)), 30);


	//EXPECT_EQ(solution(     0b0000100000000000000111111111111100001000000000001001111111111111), 14);
}
