#include "stack.h"

template <typename T> stack<T>* in_stack(stack<T>* s, T info)
{
    stack<T>* t = new stack<T>;

    t->info = info;
    t->next = s;

    return t;
}

template <typename T> stack<T>* out_stack(stack<T>* s, T* info)
{
    stack<T>* t = s;

    *info = s->info;
    s = s->next;

    delete t;
    return s;
}

template <typename T> stack<T>* out_stack(stack<T>* s)
{
    stack<T>* t = s;

    s = s->next;

    delete t;
    return s;
}
