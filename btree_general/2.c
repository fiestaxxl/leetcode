//https://leetcode.com/problems/same-tree/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.



Example 1:


Input: p = [1,2,3], q = [1,2,3]
Output: true
Example 2:


Input: p = [1,2], q = [1,null,2]
Output: false
Example 3:


Input: p = [1,2,1], q = [1,1,2]
Output: false


Constraints:

The number of nodes in both trees is in the range [0, 100].
-104 <= Node.val <= 104
*/


struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

 #include <stdlib.h>
 #include <stdbool.h>

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