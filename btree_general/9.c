//https://leetcode.com/problems/sum-root-to-leaf-numbers/description/?envType=study-plan-v2&envId=top-interview-150

/*
You are given the root of a binary tree containing digits from 0 to 9 only.

Each root-to-leaf path in the tree represents a number.

For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a 32-bit integer.

A leaf node is a node with no children.



Example 1:


Input: root = [1,2,3]
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
*/

struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
 };

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


int checkNode(struct TreeNode* root, int currentSum){

    if (!root){
        return 0;
    }

    currentSum = currentSum * 10 + root->val;

    if (!root->left && !root->right){ //is a leaf
        return currentSum;
    }

    return checkNode(root->left, currentSum) + checkNode(root->right, currentSum);
}


int sumNumbers(struct TreeNode* root) {
    if (!root){
        return 0;
    }
    return checkNode(root, 0);
}