//https://leetcode.com/problems/combinations/?envType=study-plan-v2&envId=top-interview-150

/*
Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].

You may return the answer in any order.

 

Example 1:

Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
Explanation: There are 4 choose 2 = 6 total combinations.
Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
Example 2:

Input: n = 1, k = 1
Output: [[1]]
Explanation: There is 1 choose 1 = 1 total combination.
 

Constraints:

1 <= n <= 20
1 <= k <= n
*/

// n = 5, k = 2 total 5!/(2!3!) = 10
// [[1,2], [1,3], [1,4], [1,5]. [2,3], [2,4], [2,5], [3,4], [3,5], [4,5]]


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdlib.h>

typedef struct {
    int** data;
    int len;
    int cur_pos;
} List;

long int factorial(int n){
    long int result = 1;
    for (int i=2; i<=n; i++){
        result *= i;
    }
    return result;
}

List* initList(int n, int k){
    List* list = (List*)malloc(sizeof(List));
    long int total_combinations = factorial(n)/(factorial(k)*factorial(n-k));
    list->len = total_combinations;

    list->data = (int**)malloc(total_combinations*sizeof(int*));
    for (int i=0; i<total_combinations; i++){
        list->data[i] = (int*)malloc(k*sizeof(int));
    }
    list->cur_pos = 0;
    return list;
};


void backtrack(int start, int n, int k, int* current, int depth, List* list){

    if (depth==k){
        memcpy(list->data[list->cur_pos++], current, k*sizeof(int));
        return;
    }

    for (int i = start; i<=n; i++){
        current[depth] = i;
        backtrack(i+1, n, k, current, depth+1, list);
    }
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int* current = (int*)calloc(k, sizeof(int));
    List* list = initList(n, k);

    backtrack(1, n, k, current, 0, list);

    free(current);

    *returnSize = list->cur_pos;

    *returnColumnSizes = (int*)malloc(list->cur_pos * sizeof(int));
    for (int i = 0; i < list->cur_pos; i++) {
        (*returnColumnSizes)[i] = k;
    }

    int** result = list->data;
    free(list); // Only free the struct, keep the data for the caller
    return result;
}