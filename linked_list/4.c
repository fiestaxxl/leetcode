//https://leetcode.com/problems/copy-list-with-random-pointer/description/?envType=study-plan-v2&envId=top-interview-150

/*
A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not point to any node.
Your code will only be given the head of the original linked list.

Example 1:


Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:


Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
*/

#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
    struct Node*
    random;
};

struct Node* createNode(int val){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = val;
    node->next = NULL;
    node->random = NULL;

    return node;
}

struct Node* copyRandomList(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }

    // Step 1: Clone nodes and insert them after original nodes
    struct Node* current = head;
    while (current != NULL) {
        struct Node* clone = createNode(current->val);
        clone->next = current->next;
        current->next = clone;
        current = clone->next;
    }

    // Step 2: Assign random pointers for cloned nodes
    current = head;
    while (current != NULL) {
        if (current->random != NULL) {
            current->next->random = current->random->next;
        }
        current = current->next->next;
    }

    // Step 3: Restore original list and extract the cloned list
    struct Node* dummy = createNode(0); // Dummy node for cloned list
    struct Node* cloneTail = dummy;
    current = head;

    while (current != NULL) {
        struct Node* clone = current->next;
        current->next = clone->next; // Restore original list
        cloneTail->next = clone;    // Append to cloned list
        cloneTail = clone;
        current = current->next;
    }

    struct Node* clonedHead = dummy->next;
    free(dummy); // Free the dummy node

    return clonedHead;
}