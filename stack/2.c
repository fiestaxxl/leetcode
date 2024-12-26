// https://leetcode.com/problems/simplify-path/description/?envType=study-plan-v2&envId=top-interview-150
/*
You are given an absolute path for a Unix-style file system, which always begins with a slash '/'. Your task is to transform this absolute path into its simplified canonical path.

The rules of a Unix-style file system are as follows:

A single period '.' represents the current directory.
A double period '..' represents the previous/parent directory.
Multiple consecutive slashes such as '//' and '///' are treated as a single slash '/'.
Any sequence of periods that does not match the rules above should be treated as a valid directory or file name. For example, '...' and '....' are valid directory or file names.
The simplified canonical path should follow these rules:

The path must start with a single slash '/'.
Directories within the path must be separated by exactly one slash '/'.
The path must not end with a slash '/', unless it is the root directory.
The path must not have any single or double periods ('.' and '..') used to denote current or parent directories.
Return the simplified canonical path.



Example 1:

Input: path = "/home/"

Output: "/home"

Explanation:

The trailing slash should be removed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Stack{
    char** data;
    int size;
    int top;
} Stack;

Stack* createStack(int size){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (char**)malloc(size*sizeof(char*));
    stack->size = size;
    stack->top = -1;
    return stack;
}

void freeStack(Stack* stack){
    for (int i = 0; i <= stack->top; i++) {
        free(stack->data[i]);
    }
    free(stack->data);
    free(stack);
}

bool isEmpty(Stack* stack){
    return stack->top==-1;
}

bool isFull(Stack* stack){
    return stack->top==stack->size-1;
}

void push(Stack* stack, const char* value){
    if (!isFull(stack)){
        stack->data[++stack->top] = strdup(value);
    }
}

void pop(Stack* stack){
    if (!isEmpty(stack)) {
        free(stack->data[stack->top--]);
    }
}


char* simplifyPath(char* path) {

    Stack* stack = createStack(strlen(path));
    char* token = strtok(path, "/");

    while (token) {
        if (strcmp(token, "..") == 0) {
            if (!isEmpty(stack)) {
                pop(stack);
            }
        } else if (strcmp(token, ".") != 0 && strlen(token) > 0) {
            push(stack, token);
        }
        token = strtok(NULL, "/");
    }


    // Construct the final path
    if (isEmpty(stack)) {
        freeStack(stack);
        return strdup("/");
    }

    char* result = (char*)malloc(1024 * sizeof(char)); // Allocate a large enough buffer
    result[0] = '\0';

    for (int i = 0; i <= stack->top; i++) {
        strcat(result, "/");
        strcat(result, stack->data[i]);
    }

    freeStack(stack);
    return result;
}