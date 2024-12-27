//https://leetcode.com/problems/linked-list-cycle/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given head, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.


Example 1:

Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct {
    struct ListNode* key;
    bool value;
} HashNode;

typedef struct {
    HashNode* table;
    int size;
} HashTable;


HashTable* createHashTable(int size){
    HashTable* hashtable = (HashTable*)malloc(size*sizeof(HashTable));
    hashtable->table = calloc(size, sizeof(HashNode));
    for (int i=0; i<size; i++){
        hashtable->table[i].value = false;
    }
    hashtable->size = size;
    return hashtable;
}

void freeHashTable(HashTable* hashtable){
    free(hashtable->table);
    free(hashtable);
}

size_t hashPointer(void* ptr) {
    uintptr_t addr = (uintptr_t)ptr;
    addr ^= (addr >> 16);              // Mix upper and lower bits
    addr *= 0x85ebca6b;                // Multiply by a large odd constant
    addr ^= (addr >> 13);              // More mixing
    return (size_t)addr;
}

// Insert key-value pair into hash table
void insert(HashTable* hashTable, struct ListNode* key) {
    size_t index = hashPointer(key) % hashTable->size;

    while (hashTable->table[index].value) { // Use linear probing for collision resolution
        index = (index + 1) % hashTable->size;
    }
    hashTable->table[index].key = key;
    hashTable->table[index].value = true;
}

// Search for a key in the hash table
int search(HashTable* hashTable, struct ListNode* key, bool* found) {
    size_t index = hashPointer(key) % hashTable->size;
    int originalIndex = index;

    while (hashTable->table[index].value) {
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

bool hasCycle(struct ListNode *head) {
    struct ListNode* current = head;
    HashTable* hashtable = createHashTable(1024);
    bool found = false;

    while (current != NULL) {
        search(hashtable, current, &found);
        if (found){
            freeHashTable(hashtable);
            return true;
        }
        insert(hashtable, current);
        current = current->next;
    }

    freeHashTable(hashtable);
    return false;
}