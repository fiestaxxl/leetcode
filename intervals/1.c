// https://leetcode.com/problems/summary-ranges/?envType=study-plan-v2&envId=top-interview-150

/*
You are given a sorted unique integer array nums.

A range [a,b] is the set of all integers from a to b (inclusive).

Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That is, each element of nums is covered by exactly one of the ranges, and there is no integer x such that x is in one of the ranges but not in nums.

Each range [a,b] in the list should be output as:

"a->b" if a != b
"a" if a == b


Example 1:

Input: nums = [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: The ranges are:
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** summaryRanges(int* nums, int numsSize, int* returnSize) {
    char** result = (char**)malloc(numsSize*(sizeof(char*)));
    *returnSize = 0;

    if (numsSize == 0) {
        return result; // Return empty result for empty input
    }

    int start = nums[0]; // Start of the current range

    for (int i = 1; i <= numsSize; i++) {
        // Check if the range breaks (or if we've reached the end of the array)
        if (i == numsSize || nums[i] != nums[i - 1] + 1) {
            int end = nums[i - 1]; // End of the current range
            char *range = (char *)malloc(25 * sizeof(char)); // Allocate space for a single range string
            if (start == end) {
                sprintf(range, "%d", start); // Single number range
            } else {
                sprintf(range, "%d->%d", start, end); // Range with start and end
            }
            result[*returnSize] = range; // Add range to the result
            (*returnSize)++; // Increment the result size
            if (i < numsSize) {
                start = nums[i]; // Start a new range
            }
        }
    }

    return result;
}


void printRanges(char **ranges, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", ranges[i]);
        free(ranges[i]); // Free each range string
    }
}

int main() {
    int nums[] = {0, 1, 2, 4, 5, 7};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    char **ranges = summaryRanges(nums, numsSize, &returnSize);

    printf("Ranges:\n");
    printRanges(ranges, returnSize);

    free(ranges); // Free the result array
    return 0;
}