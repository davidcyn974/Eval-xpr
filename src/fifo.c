#include "fifo.h"

#include <stdio.h>
#include <stdlib.h>

struct fifo *fifo_init(void)
{
    struct fifo *new = malloc(sizeof(struct fifo));
    if (!new)
    {
        return NULL;
    }
    new->head = NULL;
    new->tail = NULL;
    new->size = 0;
    return new;
}
size_t fifo_size(struct fifo *fifo)
{
    if (fifo->head != NULL)
    {
        return fifo->size;
    }
    return 0;
}
void fifo_push(struct fifo *fifo, int element, enum tokentype type)
{
    if (fifo->head == NULL)
    {
        struct list *new = malloc(sizeof(struct list));
        new->data = element;
        new->type = type;
        new->next = NULL;
        fifo->tail = new;
        fifo->head = new;
        fifo->size = 1;
    }
    else
    {
        struct list *new = malloc(sizeof(struct list));
        new->next = NULL;
        new->data = element;
        new->type = type;
        fifo->tail->next = new;
        fifo->tail = new;
        fifo->size++;
    }
}
int fifo_head(struct fifo *fifo)
{
    return fifo->head->data;
}
enum tokentype fifo_type(struct fifo *fifo)
{
    return fifo->head->type;
}
void fifo_print(const struct fifo *fifo)
{
    if (fifo->size != 0)
    {
        struct list *temp = fifo->head;
        while (temp != NULL)
        {
            if (temp->type == integer)
            {
                printf("%d", temp->data);
                temp = temp->next;
            }
            else
            {
                printf("%c", temp->data);
                temp = temp->next;
            }
        }
    }
}
void fifo_pop(struct fifo *fifo)
{
    if (fifo->size > 0)
    {
        struct list *tmp = fifo->head;
        fifo->head = tmp->next;
        free(tmp);
        fifo->size--;
    }
    return;
}
void fifo_clear(struct fifo *fifo)
{
    while (fifo->size > 0)
    {
        fifo_pop(fifo);
    }
}
void fifo_destroy(struct fifo *fifo)
{
    fifo_clear(fifo);
    free(fifo);
}
