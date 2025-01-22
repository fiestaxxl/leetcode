//https://leetcode.com/problems/binary-tree-right-side-view/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

 

Example 1:

Input: root = [1,2,3,null,5,null,4]

Output: [1,3,4]

Explanation:



Example 2:

Input: root = [1,2,3,4,null,null,null,5]

Output: [1,3,4,5]
*/

struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
 };
 
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueNode {
    struct TreeNode* node;
    int level;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;


QueueNode* createqNode(struct TreeNode* node, int level){
    QueueNode* qnode = (QueueNode*)malloc(sizeof(QueueNode));
    qnode->level = level;
    qnode->node = node;
    qnode->next = NULL;
    return qnode;
}

Queue* createQueue(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isEmpty(Queue* queue){
    return queue->front == NULL;
}

void enqueue(Queue* queue, struct TreeNode* node, int level){
    QueueNode* qnode = createqNode(node, level);
    if (isEmpty(queue)){
        queue->front = queue->rear = qnode;

    }
    else {
        queue->rear->next = qnode;
        queue->rear = qnode;
    }
}

QueueNode* dequeue(Queue* queue){
    if(isEmpty(queue)) {
        return NULL;
    }

    QueueNode* qnode = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL){
        queue->rear = NULL;
    }
    return qnode;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

void freeQueue(Queue* queue) {
    while (!isEmpty(queue)) {
        QueueNode* qnode = dequeue(queue);
        free(qnode);
    }
    free(queue);
}

int* rightSideView(struct TreeNode* root, int* returnSize) {
    if(!root){
        *returnSize = 0;
        return NULL;
    }
    
    int* result = NULL;
    int size = 0;
    int current_level = -1;

    Queue* queue = createQueue();
    enqueue(queue, root, 0);

    while (!isEmpty(queue)){
        QueueNode* qnode = dequeue(queue);
        int level = qnode->level;

        if (current_level<level){
            size++;
            result = realloc(result, size*sizeof(int));
            result[size-1] = qnode->node->val;
            current_level = level;
        }

        if(qnode->node->right){
            enqueue(queue, qnode->node->right, level+1);
        }
        
        if(qnode->node->left){
            enqueue(queue, qnode->node->left, level+1);
        }
        free(qnode);
    }

    *returnSize = size;
    freeQueue(queue);
    return result;
}