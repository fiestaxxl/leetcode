//https://leetcode.com/problems/permutations/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given an array nums of distinct integers, return all the possible 
permutations. You can return the answer in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:

Input: nums = [1]
Output: [[1]]
 

Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
*/
#include<stdlib.h>

typedef struct {
    int** data;
    int cur_pos;
} List;

int factorial(int n){
    int result = 1;
    for (int i=2; i<=n; i++){
        result *= i;
    }
    return result;
}

List* initList(int n){
    int num_combintations = factorial(n);

    List* list = (List*)malloc(sizeof(List));

    list->data = (int**)malloc(num_combintations * sizeof(int*));
    
    for (int i=0; i<num_combintations; i++){
        list->data[i] = (int*)malloc(n * sizeof(int));
    }
    list->cur_pos = 0;
    
    return list;
}

void backtrack(int* nums, int nums_len, int start, List* list){

    if (start == nums_len){
        memcpy(list->data[list->cur_pos++], nums, nums_len*sizeof(int));
        return;
    }
    
    int tmp;
    for (int i=start; i<nums_len; i++){
        tmp = nums[i];
        nums[i] = nums[start];
        nums[start] = tmp;

        backtrack(nums, nums_len, start+1, list);

        tmp = nums[i];
        nums[i] = nums[start];
        nums[start] = tmp;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    List* list = initList(numsSize);

    backtrack(nums, numsSize, 0, list);

    *returnSize = list->cur_pos;

    *returnColumnSizes = (int*)malloc(list->cur_pos*sizeof(int));
    for (int i=0; i<*returnSize; i++){
        (*returnColumnSizes)[i] = numsSize;
    }

    int** result = list->data;
    free(list);
    return result;
}