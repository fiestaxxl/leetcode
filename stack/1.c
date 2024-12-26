// https://leetcode.com/problems/valid-parentheses/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.


Example 1:

Input: s = "()"

Output: true
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Stack {
    int* data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (int*)malloc(capacity*sizeof(int));
    return stack;
}

void freeStack(Stack* stack){
    free(stack->data);
    free(stack);
}

bool isFull(Stack* stack){
    return stack->top==stack->capacity-1;
}

bool isEmpty(Stack* stack){
    return stack->top==-1;
}

void push(Stack* stack, int value){
    if (isFull(stack)){
        printf("Stack overflow. Cannot push %d\n", value);
        return;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack* stack){
    if (isEmpty(stack)){
        return -1;
    }
    return stack->data[stack->top--];
}


int peek(Stack* stack){
    if (isEmpty(stack)){
        return -1;
    }
    return stack->data[stack->top];
}

bool isOpening(int bracket){
    char b1 = '(';
    char b2 = '[';
    char b3 = '{';
    int round = (int)b1;
    int square = (int)b2;
    int curl = (int)b3;

    if (bracket == round || bracket==square|| bracket==curl){
        return true;
    }
    else return false;

}


bool match(int opening, int closing){
    char b1 = '(';
    char b2 = '[';
    char b3 = '{';
    int round = (int)b1;
    int square = (int)b2;
    int curl = (int)b3;

    char c1 = ')';
    char c2 = ']';
    char c3 = '}';
    int cround = (int)c1;
    int csquare = (int)c2;
    int ccurl = (int)c3;

    if ((opening==round && closing==cround) || (opening==square && closing == csquare) || (opening==curl && closing==ccurl)){
        return true;
    }
    else return false;
}

bool isValid(char* s) {
    size_t len = strlen(s);

    if(!len%2!=0){
        return false;
    }

    Stack* stack = createStack(len);

    for (int i=0; i<len; i++){
        if (isOpening((int)s[i])){
            push(stack, (int)s[i]);
        }
        else if (match(peek(stack), (int)s[i])){
            pop(stack);
        }
        else {
            freeStack(stack);
            return false;
        }
    }

    if (!isEmpty(stack)){
        freeStack(stack);
        return false;
    }
    else {
        freeStack(stack);
        return true;
    }
}