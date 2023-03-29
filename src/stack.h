#ifndef STACK_H
#define STACK_H

struct stack
{
    int data;
    struct stack *next;
};

struct stack *stack_push(struct stack *s, int e);
struct stack *stack_pop(struct stack *s);
int stack_peek(struct stack *s);
int is_a_number(char c);
int is_an_operator(char c);

#endif /* !STACK_H */
