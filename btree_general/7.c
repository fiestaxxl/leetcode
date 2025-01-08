// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/?envType=study-plan-v2&envId=top-interview-150
/*
Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.


Example 1:


Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]

*/


struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
 };

#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack {
    struct TreeNode** data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (struct TreeNode**)malloc(capacity*sizeof(struct TreeNode*));
    return stack;
}

void freeStack(Stack* stack){
    free(stack->data);
    free(stack);
}

void push(Stack* stack, struct TreeNode* value){
    stack->data[++stack->top] = value;
}

bool isEmpty(Stack* stack){
    return stack->top==-1;
}

struct TreeNode* pop(Stack* stack){
    return stack->data[stack->top--];
}


void flatten_node(struct TreeNode* root, Stack* stack){
    if (!root->left){
        if (root->right){
            root = root->right;
            flatten_node(root, stack);
        }
        else if (!isEmpty(stack)){
            root->right = pop(stack);
            root = root->right;
            flatten_node(root, stack);
        }
        else {
            return;
        }
    }

    else {
        if (root->right){
            push(stack, root->right);
        }
        root->right = root->left;
        root->left = NULL;
        root = root->right;
        flatten_node(root, stack);
    }
}

void flatten(struct TreeNode* root) {
    if (!root) {
        return;
    }

    Stack* stack = createStack(1024);

    flatten_node(root, stack);

    freeStack(stack);

}