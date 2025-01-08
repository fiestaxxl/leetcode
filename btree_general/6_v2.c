#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node with next pointer
struct Node {
    int val;
    struct Node* left;
    struct Node* right;
    struct Node* next;
};

// Queue structure for level-order traversal
struct QueueNode {
    struct Node* treeNode;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Initialize a new queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Enqueue a tree node into the queue
void enqueue(struct Queue* q, struct Node* treeNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

// Dequeue a tree node from the queue
struct Node* dequeue(struct Queue* q) {
    if (q->front == NULL) return NULL;
    struct QueueNode* temp = q->front;
    struct Node* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return treeNode;
}

// Check if the queue is empty
int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

// Main function to populate next pointers
struct Node* connect(struct Node* root) {
    if (!root) return NULL;

    // Create a queue for level-order traversal
    struct Queue* q = createQueue();
    enqueue(q, root);

    while (!isEmpty(q)) {
        int size = 0;
        struct QueueNode* temp = q->front;

        // Count the number of nodes at the current level
        while (temp) {
            size++;
            temp = temp->next;
        }

        struct Node* prev = NULL;

        // Process all nodes at the current level
        for (int i = 0; i < size; i++) {
            struct Node* curr = dequeue(q);

            // Connect the previous node to the current node
            if (prev) prev->next = curr;
            prev = curr;

            // Enqueue children of the current node
            if (curr->left) enqueue(q, curr->left);
            if (curr->right) enqueue(q, curr->right);
        }

        // Ensure the last node's next pointer is NULL
        if (prev) prev->next = NULL;
    }

    return root;
}

// Helper function to create a new tree node
struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->left = newNode->right = newNode->next = NULL;
    return newNode;
}

// Helper function to print the next pointers of each level
void printTreeNextPointers(struct Node* root) {
    struct Node* levelStart = root;
    while (levelStart) {
        struct Node* curr = levelStart;
        while (curr) {
            printf("%d -> ", curr->val);
            if (curr->next) printf("%d ", curr->next->val);
            else printf("NULL ");
            curr = curr->next;
        }
        printf("\n");
        levelStart = levelStart->left ? levelStart->left : levelStart->right;
    }
}
