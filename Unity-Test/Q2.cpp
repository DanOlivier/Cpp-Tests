#include <string>
#include <stack>
#include <algorithm>
#include <stdexcept>

using namespace std;

string solution(const string& s)
{
    stack<char> result;
    string::const_iterator it = s.begin(), it2 = s.end();
    for(; it != it2; ++it)
    {
        switch(*it)
        {
        case 'A':
        case 'B':
        case 'C':
            if(!result.empty())
            {
                if(result.top() == *it)
                {
                    result.pop();
                    continue;
                }
            }
            result.push(*it);
            break;
        default:
            throw runtime_error("Invalid value");
        }
    }
    string result2;
    while(!result.empty())
    {
        result2.push_back(result.top());
        result.pop();
    }
    reverse(result2.begin(), result2.end());
    return result2;
}

#include <gtest/gtest.h>

TEST(Unity_Q2, Trivial)
{
    EXPECT_EQ(solution("AA"), string(""));
    EXPECT_EQ(solution("AABB"), string(""));
    EXPECT_EQ(solution("ABBA"), string(""));
    EXPECT_EQ(solution("AACCAB"), "AB");
    EXPECT_EQ(solution("ABBCCAAAABBBBACCAB"), "AB");
    EXPECT_EQ(solution("AAABBBCCCABAC"), "ABCABAC");
    EXPECT_EQ(solution("ABC"), "ABC");
}
