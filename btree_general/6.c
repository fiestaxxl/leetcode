// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given a binary tree

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.
*/
struct Node {
     int val;
     struct Node *left;
     struct Node *right;
     struct Node *next;
 };

#include <stdlib.h>
#include <stdbool.h>

struct Node* findNext(struct Node* node) {
    while (node) {
        if (node->left) return node->left;
        if (node->right) return node->right;
        node = node->next;
    }
    return NULL;
}

struct Node* connect(struct Node* root) {
    if (!root) return NULL;

    // Connect left and right children
    if (root->left && root->right) {
        root->left->next = root->right;
    }

    // Connect across subtrees using findNext
    if (root->right) {
        root->right->next = findNext(root->next);
    } else if (root->left) {
        root->left->next = findNext(root->next);
    }

    // Recur on right first, then left
    connect(root->right);
    connect(root->left);

    return root;
}