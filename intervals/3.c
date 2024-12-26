//https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description/?envType=study-plan-v2&envId=top-interview-150

/*
There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the balloons.

Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

Given the array points, return the minimum number of arrows that must be shot to burst all balloons.

Example 1:

Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
*/

//[[10,16],[2,8],[1,6],[7,12]]

//[[1,6]
// [2,8]
// [7,12]
// [10,16]]

// [[2,6]
//  [7,10]]

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Comparison function for sorting intervals by their starting points
int compare(const void *a, const void *b) {
    int *intervalA = *(int **)a;
    int *intervalB = *(int **)b;

    if (intervalA[0] < intervalB[0]) return -1;
    if (intervalA[0] > intervalB[0]) return 1;
    return 0;
}

int** inner_join(int** points, int* pointsSize, int** pointsColSize, int* returnSize){
    // Allocate space for the result
    int **result = (int **)malloc(*pointsSize * sizeof(int *));
    *returnSize = 0;

    // Add the first interval to the result
    result[*returnSize] = (int *)malloc(2 * sizeof(int));
    result[*returnSize][0] = points[0][0];
    result[*returnSize][1] = points[0][1];

    // Traverse and join intervals
    for (int i = 1; i < *pointsSize; i++) {
        if (points[i][0] <= result[*returnSize][1]) {
            // Overlapping intervals, update the end time of the last interval in the result
            result[*returnSize][1] = (result[*returnSize][1] > points[i][1]) ? points[i][1] : result[*returnSize][1];
            result[*returnSize][0] = (result[*returnSize][0] > points[i][0]) ?  result[*returnSize][0] : points[i][0];

        } else {
            // Non-overlapping interval, add it to the result
            (*returnSize)++;
            result[*returnSize] = (int *)malloc(2 * sizeof(int));
            result[*returnSize][0] = points[i][0];
            result[*returnSize][1] = points[i][1];
        }
    }
    (*returnSize)++;
    for (int i = 0; i < *returnSize; i++) {
        (*pointsColSize)[i] = 2; // Each interval has two columns
    }
    return result;
}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize) {

    // Sort the intervals by their start values
    qsort(points, pointsSize, sizeof(int *), compare);

    int returnSize;
    points = inner_join(points, &pointsSize, &pointsColSize, &returnSize);

    return returnSize;
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


    int result = findMinArrowShots(arr, rows, &cols);

    // Free the dynamically allocated memory
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}