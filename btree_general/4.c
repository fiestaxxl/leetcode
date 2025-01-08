// https://leetcode.com/problems/symmetric-tree/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

Example 1:


Input: root = [1,2,2,3,4,4,3]
Output: true
Example 2:


Input: root = [1,2,2,null,3,null,3]
Output: false


Constraints:

The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100
*/

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

#include <stdlib.h>
#include <stdbool.h>

struct TreeNode* invertTree(struct TreeNode* root) {

    if (!root){
        return NULL;
    }

    if (root->left == NULL && root->right == NULL){
        return root;
    }

    struct TreeNode* tmp = root->right;
    root->right = root->left;
    root->left = tmp;

    invertTree(root->left);
    invertTree(root->right);
    return root;

}

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {

    if (p==NULL && q==NULL){
        return true;
    }

    if ((p!=NULL && q==NULL) || (p==NULL && q!=NULL)){
        return false;
    }

    if (p->val!=q->val){
        return false;
    }

    bool left = isSameTree(p->left, q->left);
    bool right = isSameTree(p->right, q->right);

    return (left && right) ? true : false;

}

bool isSymmetric(struct TreeNode* root) {
    if (root->left == NULL && root->right == NULL){
        return true;
    }

    struct TreeNode* right = root->right;

    right = invertTree(right);

    bool result = isSameTree(root->left, right);
    return result;
}