
#include "infix.h"

int order_of_precedence(char this)
{
  switch (this)
  {
  case '+':
  case '-':
    return 1;

  case 'X':
  case '/':
    return 2;

  case '^':
    return 3;
  }
  return -1;
}

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char **args, int nargs)
{
  // Write your code here
  char **postfix = malloc(sizeof(char *) * nargs);
  int postfix_length = 0;
  int stack_length = 0;

  struct double_stack *stack = double_stack_new(nargs);

  //int position_of_left_bracket;

  for (int i = 0; i < nargs; i++)
  {
    if ((args[i][0] >= '0' && args[i][0] <= '9') || (args[i][1] >= '0' && args[i][1] <= '9'))
    {
      postfix[postfix_length] = args[i];
      postfix_length++;
    }

    else if (args[i][0] == '(')
    {
      double_stack_push(stack, args[i][0]);
      stack_length++;
    }

    else if (args[i][0] == '+' || args[i][0] == '-' || args[i][0] == 'X' || args[i][0] == '/' || args[i][0] == '^')
    {
      int args_precidence = order_of_precedence(args[i][0]);
      while (order_of_precedence((char)stack->items[stack->top]) >= args_precidence)
      {
        postfix[postfix_length] = malloc(sizeof(char) * 2);
        postfix[postfix_length][0] = (char)double_stack_pop(stack);
        postfix[postfix_length][1] = '\0';
        postfix_length++;
        stack_length--;
      }
      double_stack_push(stack, args[i][0]);
      stack_length++;
    }

    else if (args[i][0] == ')')
    {
      while (stack->items[stack->top] != '(')
      {
        postfix[postfix_length] = malloc(sizeof(char) * 2);
        postfix[postfix_length][0] = (char)double_stack_pop(stack);
        postfix[postfix_length][1] = '\0';
        stack_length--;
        postfix_length++;
      }
      double_stack_pop(stack);
      stack_length--;
    }
  }
for (int i = 0; i < stack_length; i++)
  {
    postfix[postfix_length] = malloc(sizeof(char) * 2);
    postfix[postfix_length][0] = (char)double_stack_pop(stack);
    postfix[postfix_length][1] = '\0';
    postfix_length++;
  }

  return evaluate_postfix_expression(postfix, postfix_length);
}

