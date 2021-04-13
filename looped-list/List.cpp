#include "List.h"

List *generate_list(size_t n)
{
    if (0 == n)
        return nullptr;

    List *head = new List{1, nullptr};
    List *current = head;

    for (size_t i = 2; i <= n; ++i)
    {
        current->p_next = new List{i, nullptr};
        current = current->p_next;
    }

    current->p_next = head;
    return head;
}

size_t get_survivor(List *&list, size_t step)
{
    if (list == nullptr)
        return 0;

    List *current = list;

    for (; current->p_next != current;)
    {
        for (size_t i = 1; i < step; ++i)
        {
            current = current->p_next;
        }

        List *kill = current;

        for (; current->p_next != kill;)
            current = current->p_next;

        current->p_next = kill->p_next;
        current = current->p_next;

        delete kill;
    }
    list = current;
    return current->element;
}

size_t formula(size_t n, size_t k)
{
    size_t res = 0;
    for (size_t i = 1; i <= n; ++i)
        res = (res + k) % i;

    return ++res;
}