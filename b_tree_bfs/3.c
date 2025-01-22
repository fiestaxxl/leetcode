// https://leetcode.com/problems/binary-tree-level-order-traversal/?envType=study-plan-v2&envId=top-interview-150

/*
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
*/

struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
 };

#include <stdlib.h>


typedef struct QueueNode{
    int level;
    struct TreeNode* node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* rear;
    QueueNode* front;
} Queue;

QueueNode* createQnode(struct TreeNode* node, int level){
    QueueNode* qnode = (QueueNode*)malloc(sizeof(QueueNode));
    qnode->node = node;
    qnode->level = level;
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
    QueueNode* qnode = createQnode(node, level);

    if(isEmpty(queue)){
        queue->front = queue->rear = qnode;
    }
    else {
        queue->rear->next = qnode;
        queue->rear = qnode;
    }
}

QueueNode* dequeue(Queue* queue){
    if (isEmpty(queue)){
        return NULL;
    }

    QueueNode* qnode = queue->front;

    queue->front = queue->front->next;

    if(!queue->front){
        queue->rear = NULL;
    }

    return qnode;
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (!root){
        *returnSize=0;
        return NULL;
    }

    int size = 0;
    int colSize = 0;
    int current_level = 0;

    int** result = NULL;
    int* col_result = NULL;
    int* sizes = NULL;

    Queue* queue = createQueue();
    enqueue(queue, root, 0);

    while(!isEmpty(queue)){
        QueueNode* qnode = dequeue(queue);
        int level = qnode->level;

        if (level == current_level){
            col_result = realloc(col_result, (colSize+1)*sizeof(int));
            col_result[colSize++] = qnode->node->val;
        }
        else {
            current_level = level;
            result = realloc(result, (size+1)*sizeof(int*));
            sizes = realloc(sizes, (size+1)*sizeof(int));
        
            result[size] = col_result;
            sizes[size++] = colSize;

            col_result = (int*)malloc(sizeof(int));
            col_result[0] = qnode->node->val;
            colSize = 1;
        }
        if(qnode->node->left){
            enqueue(queue, qnode->node->left, level+1);
        }
        if(qnode->node->right){
            enqueue(queue, qnode->node->right, level+1);
        }
        free(qnode);
    }

    free(queue);

    result = realloc(result, (size+1)*sizeof(int*));
    sizes = realloc(sizes, (size+1)*sizeof(int));

    result[size] = col_result;
    sizes[size++] = colSize; 

    *returnSize = size;
    *returnColumnSizes = sizes;


    return result;
}