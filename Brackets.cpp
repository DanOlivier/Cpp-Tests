#include "gtest/gtest.h"

#include <string>
#include <stack>

using namespace std;

int solution(const string& s)
{
	if(s.length() >= 200000)
		return -1;

	stack<string::const_iterator> scopes;
	for(string::const_iterator it = s.begin(), it2 = s.end(); it != it2; ++it)
	{
		switch(*it)
		{
		case '(':
		case '{':
		case '[':
			scopes.push(it);
			continue;
		case ')':
			if(scopes.empty())
				return 0;
			if(*scopes.top() == '(')
			{
				scopes.pop();
				continue;
			}
			return 0;
		case '}':
			if(scopes.empty())
				return 0;
			if(*scopes.top() == '{')
			{
				scopes.pop();
				continue;
			}
			return 0;
		case ']':
			if(scopes.empty())
				return 0;
			if(*scopes.top() == '[')
			{
				scopes.pop();
				continue;
			}
			return 0;
		default:
			break;
		}
	}
	return scopes.empty();
}

TEST(Brackets, Trivial)
{
	EXPECT_EQ(solution("{"), 0);
	EXPECT_EQ(solution("]"), 0);
	EXPECT_EQ(solution("{{"), 0);
	EXPECT_EQ(solution("{[()()]}"), 1);
	EXPECT_EQ(solution("([)()]"), 0);
	EXPECT_EQ(solution("{[((((()()[][][][[[][]]]))))]()()}"), 1);
	EXPECT_EQ(solution("{[((((()()[][][][[[][]]]))))]()( ( )}"), 0);
}