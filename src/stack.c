#include "stack.h"

#include <stddef.h>
#include <stdlib.h>

// begin stack
struct stack *stack_push(struct stack *s, int e)
{
    if (s == NULL)
    {
        struct stack *single = malloc(sizeof(struct stack));
        single->data = e;
        single->next = NULL;
        return single;
    }
    struct stack *new = malloc(sizeof(struct stack));
    if (!new)
    {
        return s;
    }
    new->data = e;
    new->next = s;
    return new;
}

struct stack *stack_pop(struct stack *s)
{
    if (s == NULL)
    {
        return NULL;
    }
    if (s->next == NULL)
    {
        free(s);
        return NULL;
    }
    struct stack *new = s->next;
    free(s);
    return new;
}

int stack_peek(struct stack *s)
{
    return s->data;
}

int is_a_number(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    return 0;
}
// check whether char is an operand
int is_an_operator(char c)
{
    switch (c)
    {
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '*':
        return 1;
        break;
    case '/':
        return 1;
        break;
    case '%':
        return 1;
        break;
    case '^':
        return 1;
        break;
    case '(':
        return 2;
        break;
    case ')':
        return 3;
        break;
    default:
        return 0;
    }
    return 0;
}
