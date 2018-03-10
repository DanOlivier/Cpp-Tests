#include "gtest/gtest.h"

#include <string>

using namespace std;

int solution(const string& s)
{
	if(s.length() > 1000000)
		return -1;

	int i = 0;
	for(string::const_iterator it = s.begin(), it2 = s.end(); it != it2; ++it)
	{
		switch(*it)
		{
		case '(':
			i++;
			continue;
		case ')':
			if(i <= 0)
				return 0;
			i--;
			continue;
		default:
			break;
		}
	}
	return i == 0;
}

TEST(Brackets, Trivial)
{
	EXPECT_EQ(solution("("), 0);
	EXPECT_EQ(solution(")"), 0);
	EXPECT_EQ(solution("(("), 0);
	EXPECT_EQ(solution("((()()))"), 1);
	EXPECT_EQ(solution("(()())"), 1);
	EXPECT_EQ(solution("((((((()()()()()((()())))))))()())"), 1);
	EXPECT_EQ(solution("((((((()()()()()((()())))))))()( ( ))"), 0);
}