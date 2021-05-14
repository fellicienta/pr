#include "lib.h"

#include <algorithm>
#include <map>
#include <stack>

std::map<char, char> BRACKETS;

namespace
{
bool is_punct(const char c)
{
    if (ispunct(c))
    {
        for (auto x : BRACKETS)
            if (c == x.second)
                return false;
    }
    return true;
}

bool is_open_bracket(const char c)
{
    for (auto x : BRACKETS)
        if (c == x.first)
            return true;
    // return c == '(' || c == '[' || c == '{';
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

void fill_map()
{
    BRACKETS.emplace('(', ')');
    BRACKETS.emplace('{', '}');
    BRACKETS.emplace('[', ']');
}
} // namespace

int32_t get_error_pos(const std::string &str)
{
    fill_map();
    uint32_t counter = 0;
    //   std::stack<char> st;
    std::stack<char> error_pos;
    std::stack<std::pair<char, uint32_t>> st;
    for (auto c : str)
    {
        ++counter;
        if (is_open_bracket(c))
        {
            st.emplace(c, counter);
            //  st.push(c);
            // error_pos.push(counter);
        }
        else if (is_text(c))
        {
            continue;
        }
        else
        {
            if (st.empty())
            {
                return counter;
            }
            //      std::pair<char, uint32_t> m = st.top().value_comp();
            if (is_couple(st.top().first, c))
            {
                st.pop();
                //   error_pos.pop();
            }
            else
                return counter;
        }
    }
    if (st.empty())
        return -1;
    else
    {
        //      std::pair<char, uint32_t> m = st.top();
        return st.top().second;
    }
}

std::string check_brackets(const int32_t result)
{
    return result == -1 ? "Success" : std::to_string(result);
}