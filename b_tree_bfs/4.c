// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/?envType=study-plan-v2&envId=top-interview-150

/*
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).
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

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (!root) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int size = 0;           // Number of levels
    int colSize = 0;        // Number of nodes in the current level
    int current_level = 0;  // Current level in BFS
    int** result = NULL;    // Result array
    int* colResult = NULL;  // Array for the current level
    int* sizes = NULL;      // Sizes of each level

    Queue* queue = createQueue();
    enqueue(queue, root, 0);

    while (!isEmpty(queue)) {
        QueueNode* qnode = dequeue(queue);
        int level = qnode->level;

        if (level == current_level) {
            // Reallocate colResult to hold one more element if needed
            if (colSize == 0) {
                colResult = malloc(10 * sizeof(int));  // Initial size allocation
                if (!colResult) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
            } else if (colSize % 10 == 0) {  // Reallocate in chunks of 10
                colResult = realloc(colResult, (colSize + 10) * sizeof(int));
                if (!colResult) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
            }

            colResult[colSize++] = qnode->node->val;
        } else {
            // If level changes, store the previous level and reset colResult for the new level
            result = realloc(result, (size + 1) * sizeof(int*));
            sizes = realloc(sizes, (size + 1) * sizeof(int));
            if (!result || !sizes) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            if (current_level % 2 != 0) {
                // Reverse the current level if it's an odd level (zigzag behavior)
                for (int i = 0; i < colSize / 2; i++) {
                    int temp = colResult[i];
                    colResult[i] = colResult[colSize - 1 - i];
                    colResult[colSize - 1 - i] = temp;
                }
            }

            result[size] = colResult;
            sizes[size++] = colSize;

            // Reset colResult for the next level
            colResult = malloc(10 * sizeof(int));  // Initial size allocation
            if (!colResult) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            colSize = 1;
            colResult[0] = qnode->node->val;
            current_level = level;
        }

        if (qnode->node->left) enqueue(queue, qnode->node->left, level + 1);
        if (qnode->node->right) enqueue(queue, qnode->node->right, level + 1);

        free(qnode);
    }

    // Add the final level
    result = realloc(result, (size + 1) * sizeof(int*));
    sizes = realloc(sizes, (size + 1) * sizeof(int));
    if (!result || !sizes) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    if (current_level % 2 != 0) {
        // Reverse the final level if needed
        for (int i = 0; i < colSize / 2; i++) {
            int temp = colResult[i];
            colResult[i] = colResult[colSize - 1 - i];
            colResult[colSize - 1 - i] = temp;
        }
    }

    result[size] = colResult;
    sizes[size++] = colSize;

    *returnSize = size;

    for (int i = 0; i < size; i++) {
        (*returnColumnSizes)[i] = sizes[i];
    }

    free(sizes);
    free(queue);

    return result;
}
