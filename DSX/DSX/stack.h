#ifndef STACK_H
#define STACK_H

#include "Definitions.h"

#define STACK_MAX_SIZE 100

typedef struct stack_t {
  Data data[STACK_MAX_SIZE];
  int top;
} stack;

/* Initialise a freshly allocated stack.  Must be called before using
   any of the other stack functions. */
void stack_init(stack*);

/* Returns true if the stack is empty. */
int stack_empty(stack*);

/* Return the top element of the stack.  Undefined behaviour if the
   stack is empty. */
void* stack_top(stack*);

/* Remove the top element of the stack and return it.  Undefined
   behaviour if the stack is empty. */
void* stack_pop(stack*);

/* Push an element to the top of the stack.  Returns 0 if possible,
   any other value if there was an error (for example, if the stack is
   full or no memory could be allocated). */
int stack_push(stack*, Data);


#endif
