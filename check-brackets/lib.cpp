#include "lib.h"

#include <stack>

std::string check_brackets(std::string str)
{
    bool is_punct(char c);
    uint32_t counter = 0;
    std::stack<char> st;
    std::stack<char> error_pos;

    for (auto c : str)
    {
        ++counter;
        if (c == '(' || c == '[' || c == '{')
        {
            st.push(c);
            error_pos.push(counter);
        }
        else if (isalpha(c) || isdigit(c) || is_punct(c))
            continue;
        else
        {
            if (st.empty())
                return std::to_string(counter);

            char top = st.top();
            if ((top == '(' && c == ')') || (top == '[' && c == ']') || (top == '{' && c == '}'))
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
