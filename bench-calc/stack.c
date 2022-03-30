#include "stack.h"

struct double_stack * double_stack_new(int max_size) {
struct double_stack * result;
  // allocate space for the stack header
  result = malloc(sizeof(struct double_stack));
  result->max_size = max_size;
  result->top = 0;
  // allocate space for the data stored in the stack
  result->items = malloc(sizeof(double)*max_size);
  // return a pointer to the newly-allocated stack
  return result; 
}

int isFull(struct double_stack* this)
{
    return this->top==this->max_size;
}

int isEmpty(struct double_stack* this)
{
    return this->top==0;
}

// push a value onto the stack
void double_stack_push(struct double_stack * this, double value) {
    if(isFull(this))
    {
        return;
    }
    this->items[++this->top]= value;
}

// pop a value from the stack
double double_stack_pop(struct double_stack * this) {
    if(isEmpty(this))
    {
        return 0;
    }
    return this->items[this->top--] ;
}

double double_stack_peek(struct double_stack * this)
{
    if(isEmpty(this))
    {
        return 0;
    }
    return this->items[this->top];
}

