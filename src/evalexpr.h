#ifndef EVALEXPR_H
#define EVALEXPR_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "fifo.h"
#include "stack.h"

struct fifo *parse_input_rpn(char *string, struct fifo *fifo);

int rpn_evaluation(struct fifo *fifo);

struct fifo *shunting_yard(struct fifo *input);

#endif
