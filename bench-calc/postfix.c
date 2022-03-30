#include "postfix.h"
//#include < math.h >

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {
  // Write your code here
  struct double_stack* stack = double_stack_new(nargs);
  memset(stack->items, 0, (nargs) * sizeof(double));

  for(int i=0; i<nargs; i++)
  {
    if((args[i][0]>='0'&&args[i][0]<='9')||(args[i][1]>='0'&&args[i][1]<='9'))
    {
      double operand = atof(args[i]);
      double_stack_push(stack,operand);
    }

    else
    {
      switch(args[i][0])
      {
        double operand1, operand2, result;

        case '+' :
         operand2=double_stack_pop(stack);
         operand1=double_stack_pop(stack);
         result=operand1 + operand2;
         double_stack_push(stack,result);
         break;

         case '-':
         operand2=double_stack_pop(stack);
         operand1=double_stack_pop(stack);
         result=operand1 - operand2;
         double_stack_push(stack,result);
         break;

         case 'X':
         operand2=double_stack_pop(stack);
         operand1=double_stack_pop(stack);
         result=operand1 * operand2;
         double_stack_push(stack,result);
         break;

         case 'x':
         operand2=double_stack_pop(stack);
         operand1=double_stack_pop(stack);
         result=operand1 * operand2;
         double_stack_push(stack,result);
         break;

         case '/':
         operand2=double_stack_pop(stack);
         operand1=double_stack_pop(stack);
         result=operand1 / operand2;
         double_stack_push(stack,result);
         break;

         case '^':
         operand2=double_stack_pop(stack);
         operand1=double_stack_pop(stack);
         result=pow(operand1,operand2);
         double_stack_push(stack,result);
         break;
  
      }
    }
  } 
  return double_stack_pop(stack);
}
