//https://leetcode.com/problems/merge-intervals/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>

// Comparison function for sorting intervals by their starting points
int compare(const void *a, const void *b) {
    int *intervalA = *(int **)a;
    int *intervalB = *(int **)b;
    return intervalA[0] - intervalB[0];
}


int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    if (intervalsSize == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    // Sort the intervals by their start values
    qsort(intervals, intervalsSize, sizeof(int *), compare);


    // Allocate space for the result
    int **result = (int **)malloc(intervalsSize * sizeof(int *));
    *returnColumnSizes = (int *)malloc(intervalsSize * sizeof(int));
    *returnSize = 0;

    // Add the first interval to the result
    result[*returnSize] = (int *)malloc(2 * sizeof(int));
    result[*returnSize][0] = intervals[0][0];
    result[*returnSize][1] = intervals[0][1];

    // Traverse and merge intervals
    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i][0] <= result[*returnSize][1]) {
            // Overlapping intervals, update the end time of the last interval in the result
            result[*returnSize][1] = (result[*returnSize][1] > intervals[i][1]) ? result[*returnSize][1] : intervals[i][1];
        } else {
            // Non-overlapping interval, add it to the result
            (*returnSize)++;
            result[*returnSize] = (int *)malloc(2 * sizeof(int));
            result[*returnSize][0] = intervals[i][0];
            result[*returnSize][1] = intervals[i][1];
        }
    }

    // Adjust the final return size
    (*returnSize)++;
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2; // Each interval has two columns
    }
    return result;
}

void main(){
    int cols = 2;
    int rows = 5;

    int **arr = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        arr[i] = (int *)malloc(cols * sizeof(int));
    }

    // Initialize the 2D array
    int values[5][2] = {
        {1, 2},
        {4, 7},
        {5, 9},
        {10, 14},
        {11, 20}};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = values[i][j];
        }
    }

    int returnSize;
    int matrixColSize = rows;
    int *returnColumnSize = malloc(2*sizeof(int));

    int** result = merge(arr, rows, &cols, &returnSize, &returnColumnSize);

    printf("SIZE: %d\n", returnSize);
    for (int i=0; i<returnSize; i++){
        for (int j=0; j<2; j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);

    // Free the dynamically allocated memory
    for (int i = 0; i < returnSize; i++)
    {
        free(result[i]);
    }
    free(result);

    free(returnColumnSize);
}