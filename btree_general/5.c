/*
preorder = [3,9,10,20,15,11,7], inorder = [10,9,3,11,15,20,7]
preorder = [1,2,4,6,5,3,7,8,9,10], inorder = [4,2,5,6,1,3,8,9,7,10]
preorder = [4,5,3,17,2,6,7,1,9,8,10,11,13,14,15,20,19], inorder = [3,2,6,17,1,7,5,9,8,4,10,14,13,11,20,15,19]
*/

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };

#include <stdlib.h>
#include <stdbool.h>

struct TreeNode* createNode(int val){
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
}

int searchValue(int* inorder, int value, int s, int e){

    for (int i=s; i<e+1; i++){
        if (inorder[i]==value){
            return i;
        }
    }
    return -1;
}

struct TreeNode* recBuildTree(int* preorder, int* inorder, int s, int e, int cur_idx, int max_len){
    if (s>e || cur_idx==max_len){
        return NULL;
    }

    int index = searchValue(inorder, preorder[cur_idx], s, e);

    if (index!=-1){
        struct TreeNode* node = createNode(preorder[cur_idx]);
        cur_idx++;

        node->left = recBuildTree(preorder, inorder, s, index-1, cur_idx, max_len);
        node->right = recBuildTree(preorder, inorder, index+1, e, cur_idx, max_len);
        return node;
    }
    else{
        cur_idx++;
        return NULL;
    }
}
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    struct TreeNode* root = recBuildTree(preorder, inorder, 0, inorderSize-1, 0, preorder);
    return root;
}