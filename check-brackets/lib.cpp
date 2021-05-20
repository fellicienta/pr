#include "lib.h"

#include <algorithm>
#include <map>
#include <stack>

const uint32_t SUCCESS = std::numeric_limits<uint32_t>::max();
std::map<char, char> BRACKETS = {{'(', ')'}, {'{', '}'}, {'[', ']'}};

namespace
{
bool is_punct(const char c)
{
    return ispunct(c) &&
           !std::any_of(BRACKETS.begin(), BRACKETS.end(), [&](const std::pair<char, char> &x) {
               return c == x.first || c == x.second;
           });
}

bool is_open_bracket(const char c)
{
    return std::any_of(BRACKETS.begin(), BRACKETS.end(),
                       [&](const std::pair<char, char> &x) { return c == x.first; });
}

bool is_text(const char c)
{
    return isalpha(c) || isdigit(c) || is_punct(c);
}

bool is_couple(const char top, const char c)
{
    return BRACKETS[top] == c;
}

} // namespace

uint32_t check_brackets(const std::string &str)
{
    uint32_t counter = 0;
    std::stack<std::pair<char, uint32_t>> st;

    for (auto c : str)
    {
        ++counter;
        if (is_text(c))
            continue;
        else if (is_open_bracket(c))
            st.emplace(c, counter);
        else
        {
            if (st.empty() || !is_couple(st.top().first, c))
                return counter;
            st.pop();
        }
    }

    return st.empty() ? SUCCESS : st.top().second;
}

std::string check_result(const int32_t result)
{
    return result == SUCCESS ? "Success" : std::to_string(result);
}
