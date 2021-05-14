#include "lib.h"

#include <stack>

std::string check_brackets(std::string str)
{
    bool is_punct(char c);
    bool is_open_bracket(char c);
    bool is_text(char c);
    bool is_couple(char top, char c);

    uint32_t counter = 0;
    std::stack<char> st;
    std::stack<char> error_pos;

    for (auto c : str)
    {
        ++counter;
        if (is_open_bracket(c))
        {
            st.push(c);
            error_pos.push(counter);
        }
        else if (is_text(c))
            continue;
        else
        {
            if (st.empty())
                return std::to_string(counter);

            if (is_couple(st.top(), c))
            {
                st.pop();
                error_pos.pop();
            }
            else
                return std::to_string(counter);
        }
    }
    if (st.empty())
        return "Success";
    else
        return std::to_string(error_pos.top());
}

bool is_punct(char c)
{
    return ispunct(c) && c != ']' && c != '}' && c != ')';
}

bool is_open_bracket(char c)
{
    return c == '(' || c == '[' || c == '{';
}

bool is_text(char c)
{
    return isalpha(c) || isdigit(c) || is_punct(c);
}

bool is_couple(char top, char c)
{
    return (top == '(' && c == ')') || (top == '[' && c == ']') || (top == '{' && c == '}');
}