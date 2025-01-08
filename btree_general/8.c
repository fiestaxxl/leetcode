// https://leetcode.com/problems/path-sum/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.

Example 1:

Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path with the target sum is shown.
*/


struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
 };

#include <stdbool.h>
#include <stdlib.h>

bool checkNode(struct TreeNode* root, int currentSum, int targetSum) {
    if (!root) {
        return false;
    }

    currentSum += root->val;

    // Check if the current node is a leaf and the sum matches the targetSum
    if (!root->left && !root->right) {
        return currentSum == targetSum;
    }

    // Recurse into left and right subtrees
    return checkNode(root->left, currentSum, targetSum) ||
           checkNode(root->right, currentSum, targetSum);
}

bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (!root) {
        return false;
    }
    return checkNode(root, 0, targetSum);
}