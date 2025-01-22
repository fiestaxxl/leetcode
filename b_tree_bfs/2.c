//https://leetcode.com/problems/average-of-levels-in-binary-tree/?envType=study-plan-v2&envId=top-interview-150

/*
Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. Answers within 10-5 of the actual answer will be accepted.
*/
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
 };

#include <stdlib.h>

typedef struct QueueNode {
    int level;
    struct TreeNode* node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

QueueNode* createQnode(struct TreeNode* node, int level){
    QueueNode* qnode = (QueueNode*)malloc(sizeof(QueueNode));
    qnode->level = level;
    qnode->node = node;
    qnode->next = NULL;
    return qnode;
}

Queue* createQueue(){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->rear = NULL;
    queue->front = NULL;
    return queue;
}

int isEmpty(Queue* queue){
    return queue->front == NULL;
}

void enqueue(Queue* queue, struct TreeNode* node, int level){
    QueueNode* qnode = createQnode(node, level);

    if (isEmpty(queue)) {
        queue->front = queue->rear = qnode;
    }
    else {
        queue->rear->next = qnode;
        queue->rear = qnode;
    }

}

QueueNode* dequeue(Queue* queue){
    if (isEmpty(queue)) return NULL;

    QueueNode* qnode = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) queue->rear = NULL;

    return qnode;
}

void freeQueue(Queue* queue){
    while(!isEmpty(queue)){
        QueueNode* qnode = dequeue(queue);
        free(qnode);
    }
    free(queue);
}

double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    if (!root){
        *returnSize = 0;
        return NULL;
    }

    int size = 0;
    int current_level = 0;
    int current_res = 0;
    int cur_num = 0;
    double* result = NULL;

    Queue* queue = createQueue();
    enqueue(queue, root, 0);

    while(!isEmpty(queue)){
        QueueNode* qnode = dequeue(queue);
        
        int level = qnode->level;

        if (current_level == level){
            current_res += qnode->node->val;
            cur_num++;
        }
        else {
            current_level = level;
            result = realloc(result, (size+1)*sizeof(double));
            result[size++] = (double)current_res/cur_num;
            current_res = qnode->node->val;
            cur_num = 1;  
        }

        if (qnode->node->right) enqueue(queue, qnode->node->right, level+1);
        if (qnode->node->left) enqueue(queue, qnode->node->left, level+1);

        free(qnode);

    }

    // Add the final level's average
    result = realloc(result, (size + 1) * sizeof(double));
    result[size++] = (double)current_res / cur_num;


    *returnSize = size;
    freeQueue(queue);
    return result;
}