#include "stack.h"

void push(struct Stack *stack, struct Point point) {
    stack->points[++stack->top] = point;
}

struct Point pop(struct Stack *stack) {
    return stack->points[stack->top--];
}

struct Point nextToTop(struct Stack *stack) {
    return stack->points[stack->top - 1];
}

struct Point top(struct Stack stack) {
    return stack.points[stack.top];
}

struct Stack copyStack(struct Stack originalStack) {
    // Allocate memory for the new stack
    struct Stack newStack;
    newStack.top = originalStack.top;

    // Copy the values of the points array from the original stack to the new stack
    for (int i = 0; i <= newStack.top; i++) {
        newStack.points[i] = originalStack.points[i];
    }

    return newStack;
}