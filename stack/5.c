// https://leetcode.com/problems/basic-calculator/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "1 + 1"
Output: 2
Example 2:

Input: s = " 2-1 + 2 "
Output: 3
Example 3:

Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23
 

Constraints:

1 <= s.length <= 3 * 105
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
There will be no two consecutive operators in the input.
Every number and running calculation will fit in a signed 32-bit integer.
*/


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

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







typedef struct {
    char** data;
    int top;
    int size;
} StackChar;

StackChar* createStackChar(int size){
    StackChar* stack = (StackChar*)malloc(sizeof(StackChar));
    stack->data = (char**)malloc(size*sizeof(char*));
    stack->top = -1;
    stack->size = size;
    return stack;
}

// Check if the stack is empty
int isEmptyChar(StackChar* s) {
    return s->top == -1;
}


void pushChar(StackChar* stack, char* value){
    stack->data[++stack->top] = strdup(value);
}

char* popChar(StackChar* stack){
    return stack->data[stack->top--];
}


void freeStackChar(StackChar* stack) {
    while (!isEmptyChar(stack)) {
        free(popChar(stack));
    }
    free(stack->data);
    free(stack);
}

int precedence(char op){
    if (op == '+' || op ==  '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int isOperator(char c){
    return c=='+' || c=='-' || c=='*' || c=='/';
}

void infixToPostfix(char* infix, char** postfix, int* postfixSize) {
    StackChar* stack = createStackChar(strlen(infix));

    int j = 0;
    int i = 0;

    while(infix[i]!='\0') {
        if (infix[i]== ' '){
            i++;
            continue;
        }
        if(isdigit(infix[i])){
            int start = i;
            while (isdigit(infix[i])) i++;
            char* num = strndup(&infix[start], i - start);
            postfix[j++] = num;
        }
        else if (infix[i] == '('){
            char paren[2] = {'(', '\0'};
            pushChar(stack, paren);
            i++;
        }
        else if (infix[i]==')'){
            while (strcmp(stack->data[stack->top], "(")!=0){
                postfix[j++] = popChar(stack);
            }

            popChar(stack);
            i++;
            
        }
        else if (infix[i] == '-') {
            // Handle unary minus
            if (i == 0 || infix[i - 1] == '(' || infix[i - 1] == ' ' || isOperator(infix[i - 1])) {
                // This is a unary minus (either at the start or after '(' or an operator)
                i++; // Skip '-' and read the number
                int start = i;
                while (isdigit(infix[i])) i++;
                char* num = strndup(&infix[start - 1], i - start + 1); // Include the '-'
                postfix[j++] = num;
            } else {
                // Push '-' as a binary operator
                char op[2] = {'-', '\0'};
                while (!isEmptyChar(stack) && precedence(stack->data[stack->top][0]) >= precedence(op[0])) {
                    postfix[j++] = popChar(stack);
                }
                pushChar(stack, op);
                i++;
            }
        }
        else if (infix[i] == '+' || infix[i] == '*' || infix[i] == '/') {
            // Handle binary operators +, *, /
            char op[2] = {infix[i], '\0'};
            while (!isEmptyChar(stack) && precedence(stack->data[stack->top][0]) >= precedence(op[0])) {
                postfix[j++] = popChar(stack);
            }
            pushChar(stack, op);
            i++;
        }

    }

    while (!isEmptyChar(stack)) {
        postfix[j++] = popChar(stack);
    }

    *postfixSize = j; // Update the size of the postfix array
    freeStackChar(stack);

}

int calculate(char* s) {
    char**  postfix = (char**)malloc(strlen(s)*sizeof(char*));
    int postfixSize = 0;

    infixToPostfix(s, postfix, &postfixSize);

    for (int i=0; i<postfixSize; i++){
        printf("%s", postfix[i]);
    }
    printf("\n");

    int result = evalRPN(postfix, postfixSize);

    for (int i = 0; i < postfixSize; i++) {
        free(postfix[i]);
    }
    free(postfix);

    return result;
}

// Main function
int main() {
    char expression[] = "-(3+(4+5))";
    printf("Result: %d\n", calculate(expression));
    return 0;
}