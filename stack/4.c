// https://leetcode.com/problems/evaluate-reverse-polish-notation/description/?envType=study-plan-v2&envId=top-interview-150

/*
You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

Evaluate the expression. Return an integer that represents the value of the expression.

Note that:

The valid operators are '+', '-', '*', and '/'.
Each operand may be an integer or another expression.
The division between two integers always truncates toward zero.
There will not be any division by zero.
The input represents a valid arithmetic expression in a reverse polish notation.
The answer and all the intermediate calculations can be represented in a 32-bit integer.

Example 1:

Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
*/

#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int top;
} Stack;

Stack* createStack(int size){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(size*sizeof(int));
    stack->top = -1;
    return stack;
}

void push(Stack* stack, int value){
    stack->data[++stack->top] = value;
}

int pop(Stack* stack){
    return stack->data[stack->top--];
}

void freeStack(Stack* stack){
    free(stack->data);
    free(stack);
}

int evalRPN(char** tokens, int tokensSize) {
    if (tokensSize==1){
        return atoi(tokens[0]);
    }

    Stack* stack = createStack(tokensSize);

    for (int i=0; i<tokensSize; i++){
        if(strcmp(tokens[i], "+") == 0 || strcmp(tokens[i], "-") == 0|| strcmp(tokens[i], "*") == 0|| strcmp(tokens[i], "/") == 0){
            int a = pop(stack);
            int b = pop(stack);
            int c = strcmp(tokens[i], "+") == 0 ? b + a :
                    strcmp(tokens[i], "-") == 0 ? b - a :
                    strcmp(tokens[i], "*") == 0 ? b * a : b / a;
            push(stack, c);
        }
        else {
            push(stack, atoi(tokens[i]));
        }
    }

    int result = pop(stack);
    freeStack(stack);
    return result;
}