//https://leetcode.com/problems/3sum/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int key;
    int value;
    bool isValid; // To differentiate between empty and valid entries
} HashNode;

typedef struct {
    HashNode* table;
    int size;
} HashTable;

// Hash function
int hashFunction(int key, int size) {
    return (key % size + size) % size; // Handle negative keys
}

// Initialize hash table
HashTable* createHashTable(int size) {
    HashTable* hashTable = malloc(sizeof(HashTable));
    hashTable->table = calloc(size, sizeof(HashNode));
    hashTable->size = size;

    for (int i = 0; i < size; i++) {
        hashTable->table[i].isValid = false; // Mark all entries as invalid initially
    }
    return hashTable;
}

// Insert key-value pair into hash table
void insert(HashTable* hashTable, int key, int value) {
    int index = hashFunction(key, hashTable->size);
    while (hashTable->table[index].isValid) { // Use linear probing for collision resolution
        index = (index + 1) % hashTable->size;
    }
    hashTable->table[index].key = key;
    hashTable->table[index].value = value;
    hashTable->table[index].isValid = true; // Mark entry as valid
}

// Search for a key in the hash table
int search(HashTable* hashTable, int key, bool* found) {
    int index = hashFunction(key, hashTable->size);
    int originalIndex = index;

    while (hashTable->table[index].isValid) {
        if (hashTable->table[index].key == key) {
            *found = true;
            return hashTable->table[index].value;
        }
        index = (index + 1) % hashTable->size;
        if (index == originalIndex) break; // Stop if we've looped through the table
    }

    *found = false;
    return -1;
}

// Free hash table memory
void freeHashTable(HashTable* hashTable) {
    free(hashTable->table);
    free(hashTable);
}

// Comparison function for qsort
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}


int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    // Allocate memory for results
    int** result = malloc(numsSize * numsSize * sizeof(int*));
    *returnColumnSizes = malloc(numsSize * numsSize * sizeof(int));

    // Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

     for (int i = 0; i < numsSize - 2; i++) {

        if(nums[i] > 0){  //If number fixed is +ve, stop there because we can't make it zero by searching after it.
            break;
        }
        // Skip duplicates
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }


        // Create a hash table for two-sum
        HashTable* hashTable = createHashTable(numsSize*2);


        for (int j = i + 1; j < numsSize; j++) {
            bool found = false;
            int complement = -nums[i] - nums[j];

            int complementIndex = search(hashTable, complement, &found);

            if (found){
                result[*returnSize] = malloc(3*sizeof(int));
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[j];
                result[*returnSize][2] = complement;
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                // Skip duplicates for the second number
                while (j + 1 < numsSize && nums[j] == nums[j + 1]) {
                    j++;
                }
            }
            else {
                insert(hashTable, nums[j], j);
            }
        }
        freeHashTable(hashTable);

     }
    return result;
}

int main() {
    int nums[] = {82597,-9243,62390,83030,-97960,-26521,-61011};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* returnColumnSizes;

    int** result = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);

    // Write results to a file
    FILE* file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    fprintf(file, "Unique triplets:\n");
    for (int i = 0; i < returnSize; i++) {
        fprintf(file, "[%d, %d, %d]\n", result[i][0], result[i][1], result[i][2]);
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    fclose(file);
    printf("Results have been written to output.txt\n");

    return 0;
}
