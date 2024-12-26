// https://leetcode.com/problems/min-stack/description/?envType=study-plan-v2&envId=top-interview-150

/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the MinStack class:

MinStack() initializes the stack object.
void push(int val) pushes the element val onto the stack.
void pop() removes the element on the top of the stack.
int top() gets the top element of the stack.
int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.



Example 1:

Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
*/

#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* data;
    int top;
    int* mins;
    int capacity;
} MinStack;


MinStack* minStackCreate() {
    MinStack* stack = (MinStack*)malloc(sizeof(MinStack));
    stack->capacity = 1024;
    stack->data = (int*)malloc(stack->capacity*sizeof(int));
    stack->mins = (int*)malloc(stack->capacity*sizeof(int));
    stack->top = -1;
    return stack;
}

void resizeStack(MinStack* obj) {
    obj->capacity *= 2;
    obj->data = (int*)realloc(obj->data, obj->capacity * sizeof(int));
    obj->mins = (int*)realloc(obj->mins, obj->capacity * sizeof(int));
}

void minStackPush(MinStack* obj, int val) {
    if (obj->top == obj->capacity - 1) {
        resizeStack(obj);
    }

    obj->data[++obj->top] = val;

    // Maintain minimum for this value
    if (obj->top == 0) {
        obj->mins[obj->top] = val;
    } else {
        obj->mins[obj->top] = (val < obj->mins[obj->top - 1]) ? val : obj->mins[obj->top - 1];
    }
}

void minStackPop(MinStack* obj) {
    if (obj->top >= 0) {
        obj->top--;
    }
}

int minStackTop(MinStack* obj) {
    return (obj->top >= 0) ? obj->data[obj->top] : INT_MIN;
}

int minStackGetMin(MinStack* obj) {
    return (obj->top >= 0) ? obj->mins[obj->top] : INT_MIN;
}

void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj->mins);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/