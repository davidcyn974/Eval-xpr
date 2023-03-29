#include "evalexpr.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"
#include "stack.h"

struct fifo *parse_input_rpn(char *string, struct fifo *fifo)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (string[i] >= '0' && string[i] <= '9')
        {
            int res = 0;
            while (string[i] >= '0' && string[i] <= '9')
            {
                res = res * 10 + string[i] - '0';
                i++;
            }
            fifo_push(fifo, res, integer);
        }
        else if (is_an_operator(string[i]))
        {
            fifo_push(fifo, string[i], operator);
            i++;
        }
        else if (isspace(string[i]))
        {
            i++;
        }
    }
    return fifo;
}
int myPow(int x, int n)
{
    int number = 1;

    for (int i = 0; i < n; ++i)
        number *= x;

    return number;
}

int rpn_evaluation(struct fifo *fifo)
{
    int stack_elt1 = 0;
    int stack_elt2 = 0;
    struct stack *stack = NULL;
    while (fifo->size > 0)
    {
        struct list *current = fifo->head;
        if (current->type == operator)
        {
            stack_elt1 = stack_peek(stack);
            stack = stack_pop(stack);
            stack_elt2 = stack_peek(stack);
            stack = stack_pop(stack);
            switch (current->data)
            {
            case '+':
                stack = stack_push(stack, stack_elt2 + stack_elt1);
                break;
            case '-':
                stack = stack_push(stack, stack_elt2 - stack_elt1);
                break;
            case '*':
                stack = stack_push(stack, stack_elt2 * stack_elt1);
                break;
            case '/':
                stack = stack_push(stack, stack_elt2 / stack_elt1);
                break;
            case '%':
                stack = stack_push(stack, stack_elt2 % stack_elt1);
                break;
            case '^':
                stack = stack_push(stack, myPow(stack_elt2, stack_elt1));
                break;
            default:
                break;
            }
            fifo_pop(fifo);
        }
        else
        {
            stack = stack_push(stack, (fifo_head(fifo)));
            fifo_pop(fifo);
        }
    }
    int result = stack->data;
    if (stack)
    {
        free(stack);
    }
    fifo_destroy(fifo);
    return result;
}

int precedence(int x)
{
    switch (x)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 4;
    }
}

struct fifo *shunting_yard(struct fifo *input)
{
    struct fifo *output = fifo_init();
    struct stack *stack = NULL;
    while (input->head)
    {
        struct list *item = input->head;
        if (item->type == integer)
        {
            fifo_push(output, item->data, item->type);
            fifo_pop(input);
        }
        else
        {
            int o1 = item->data;
            if (item->data == '(')
            {
                stack = stack_push(stack, '(');
                fifo_pop(input);
            }
            else if (item->data == ')')
            {
                while (stack && stack->data != ')')
                {
                    int temp = stack->data;
                    stack = stack_pop(stack);
                    fifo_push(output, temp, operator);
                }
                if (!stack || stack->data != ')')
                {
                    printf("error\n");
                }
                else
                {
                    stack = stack_pop(stack);
                    fifo_pop(input);
                }
            }
            else
            {
                if (stack)
                {
                    int o2 = stack->data;
                    while (
                        stack
                        && ((o2 != '(' && precedence(o2) > precedence(o1))
                            || (precedence(o1) == precedence(o2) && o1 != '^')))
                    {
                        o2 = stack->data;
                        stack = stack_pop(stack);
                        fifo_push(output, o2, operator);
                    }
                }
                stack = stack_push(stack, o1);
                fifo_pop(input);
            }
        }
    }
    while (stack)
    {
        if (stack->data != '(')
        {
            int temp = stack->data;
            stack = stack_pop(stack);
            fifo_push(output, temp, operator);
        }
        else
        {
            printf("error mismatch ( ) \n");
        }
    }
    if (stack)
    {
        free(stack);
    }
    if (input)
    {
        free(input);
    }
    return output;
}
