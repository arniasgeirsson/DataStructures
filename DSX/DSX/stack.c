#include <stdlib.h>
#include "stack.h"

void stack_init(stack* stack) {
  stack->top = -1;
}

int stack_empty(stack* stack) {
  return stack->top == -1;
}

void* stack_top(stack* stack) {
  return stack->data[stack->top];
}

void* stack_pop(stack* stack) {
  return stack->data[stack->top--];
}

int stack_push(stack* stack, Data data) {
  if (stack->top == STACK_MAX_SIZE-1) {
    return 1;
  } else {
    stack->data[++stack->top] = data;
    return 0;
  }
}
