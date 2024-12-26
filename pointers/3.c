// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
The tests are generated such that there is exactly one solution. You may not use the same element twice.
Your solution must use only constant extra space.

Example 1:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].

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
    int tries = 0;
    while (hashTable->table[index].isValid) { // Use linear probing for collision resolution
        index = (index + 1) % hashTable->size;
        tries++;
        if (tries==3){
            break;
            }
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


int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    HashTable* hashTable = createHashTable(numbersSize * 2); // Create a hash table
    int* result = malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numbersSize; i++) {
        bool found = false;
        int complement = target - numbers[i]; // Calculate the complement
        int complementIndex = search(hashTable, complement, &found);

        if (found) {
            result[0] = complementIndex+1;
            result[1] = i+1;
            freeHashTable(hashTable);
            return result;
        }

        // Insert the current number and its index into the hash table
        insert(hashTable, numbers[i], i);
    }

    // If no solution is found
    *returnSize = 0;
    freeHashTable(hashTable);
    free(result);
    return NULL;
}

int main() {
    int numbers[] = {0, 6, 15, 11, 9};
    int size = 5;//(int)(sizeof(numbers)/sizeof(numbers[0]));
    int target = 9;
    int returnSize = 0;

    int* result = twoSum(numbers, size, target, &returnSize);

    if (result != NULL && returnSize == 2) {
        printf("Indices: %d, %d\n", result[0], result[1]);
        free(result);
    } else {
        printf("No two sum solution found.\n");
    }


    return 0;
}