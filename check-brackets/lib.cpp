#include "lib.h"

#include <algorithm>
#include <map>
#include <stack>

const uint32_t SUCCESS = std::numeric_limits<uint32_t>::max();
std::map<char, char> BRACKETS;

namespace
{
bool is_punct(const char c)
{
    if (ispunct(c))
        for (auto x : BRACKETS)
            if (c == x.first || c == x.second)
                return false;
    return true;
}

bool is_open_bracket(const char c)
{
    for (auto x : BRACKETS)
        if (c == x.first)
            return true;
    return false;
}

bool is_text(const char c)
{
    return isalpha(c) || isdigit(c) || is_punct(c);
}

bool is_couple(char top, const char c)
{
    for (auto x : BRACKETS)
        if (top == x.first && c == x.second)
            return true;
    return false;
}

} // namespace

uint32_t check_brackets(const std::string &str)
{
    set_brackets();
    uint32_t counter = 0;
    std::stack<std::pair<char, uint32_t>> st;

    for (auto c : str)
    {
        ++counter;
        if (is_text(c))
        {
            continue;
        }
        else if (is_open_bracket(c))
        {
            st.emplace(c, counter);
        }
        else
        {
            if (st.empty())
            {
                return counter;
            }
            if (is_couple(st.top().first, c))
            {
                st.pop();
            }
            else
            {
                return counter;
            }
        }
    }

    if (st.empty())
    {
        return SUCCESS;
    }
    else
    {
        return st.top().second;
    }
}

std::string check_result(const int32_t result)
{
    return result == SUCCESS ? "Success" : std::to_string(result);
}

void set_brackets()
{
    BRACKETS.emplace('(', ')');
    BRACKETS.emplace('{', '}');
    BRACKETS.emplace('[', ']');
}
