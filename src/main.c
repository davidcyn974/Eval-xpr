#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evalexpr.h"
#include "fifo.h"
#include "my_strcmp.h"
#include "stack.h"

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        return 4;
    }
    if (argc == 2 && !strcmp(argv[1], "-rpn") == 0)
    {
        return 4;
    }
    char buffer[200];
    size_t input_len = fread(buffer, 1, 100, stdin);
    if (input_len == 1)
    {
        return 0;
    }
    buffer[input_len] = '\0';
    struct fifo *fifo = fifo_init();
    fifo = parse_input_rpn(buffer, fifo);
    fifo = shunting_yard(fifo);
    printf("%d\n", rpn_evaluation(fifo));
    return 0;
}
