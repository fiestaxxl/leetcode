// https://leetcode.com/problems/combination-sum/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the 
frequency
 of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

 

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.
Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Example 3:

Input: candidates = [2], target = 1
Output: []
 

Constraints:

1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdlib.h>

int compare(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

typedef struct {
    int** data;
    int cur_pos;
    int* sizes;
    int capacity;
} List;

List* initList(int initialCapacity) {
    List* list = (List*)malloc(sizeof(List));
    list->data = (int**)malloc(initialCapacity * sizeof(int*));
    list->sizes = (int*)malloc(initialCapacity * sizeof(int));
    list->cur_pos = 0;
    list->capacity = initialCapacity;
    return list;
}

void addToList(List* list, int* combination, int size){
    if (list->cur_pos == list->capacity){
        list->capacity *= 2;
        list->data = (int**)realloc(list->data, list->capacity * sizeof(int*));
        list->sizes = (int*)realloc(list->sizes, list->capacity * sizeof(int));
    }

    list->data[list->cur_pos] = (int*)malloc(size*sizeof(int));
    memcpy(list->data[list->cur_pos], combination, size*sizeof(int));
    list->sizes[list->cur_pos++] = size;
}

void backtrack(int* current, int current_sum, int cur_len, int index, int target, int* candidates, int candidatesSize, List* list){
    
    if (current_sum==target){
        addToList(list, current, cur_len);
        return;
    }

    for (int i=index; i<candidatesSize; i++){
        if(current_sum+candidates[i]>target){
            break;
        }
        current[cur_len] = candidates[i];
        backtrack(current, current_sum+candidates[i], cur_len+1, i, target, candidates, candidatesSize, list);
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    
    qsort(candidates, candidatesSize, sizeof(int), compare);


    List* list = initList(candidatesSize);

    int* current = (int*)malloc(target*sizeof(int));

    backtrack(current, 0, 0, 0, target, candidates, candidatesSize, list);

    free(current);

    int** result = list->data;
    *returnSize = list->cur_pos;

    *returnColumnSizes = (int*)malloc(list->cur_pos*sizeof(int));
    for (int i=0; i<*returnSize; i++){
        (*returnColumnSizes)[i] = list->sizes[i];
    }

    free(list->sizes);
    free(list);
    return result;
    
}