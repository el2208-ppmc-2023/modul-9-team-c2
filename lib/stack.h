#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "point.h"

struct Stack {
    int top;
    struct Point points[100];
};


void push(struct Stack *stack, struct Point point);

struct Point pop(struct Stack *stack);

struct Point top(struct Stack stack);

struct Point nextToTop(struct Stack *stack);

struct Stack copyStack(struct Stack stack);

#endif
