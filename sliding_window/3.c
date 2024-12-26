//https://leetcode.com/problems/minimum-window-substring/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given two strings s and t of lengths m and n respectively, return the minimum window
substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct {
    bool value;
    int key;
    bool isValid; // To differentiate between empty and valid entries
} HashNode;

// Hash table structure
typedef struct {
    HashNode* table;
    int size;
} HashTable;


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

// Initialize the hash table
HashTable* initHashTable(int num_chars) {
    HashTable* hashtable = malloc(sizeof(HashTable));
    hashtable->table = calloc(num_chars, sizeof(HashNode));
    hashtable->size = num_chars;
    for (int i = 0; i < num_chars; i++) {
        hashtable->table[i].isValid = false;  // All characters are initially not present
    }
    return hashtable;
}

// Free hash table memory
void freeHashTable(HashTable* hashTable) {
    free(hashTable->table);
    free(hashTable);
}

// Hash function to map a character to an index in the hash table
int hashFunction(char c) {
    return (int)c;  // Simple hash function for ASCII characters
}

// Check if the character is unique (not already in the hash table)
bool isUnique(HashTable* hashTable, char c) {
    int index = hashFunction(c);
    return !hashTable->table[index];  // If false, the character is not present
}

// Insert key-value pair into hash table
void insert(HashTable* hashTable, char newChar) {
    int index = hashFunction(newChar);
    while (hashTable->table[index].isValid) { // Use linear probing for collision resolution
        index = (index + 1) % hashTable->size;
    }
    hashTable->table[index].key = index;
    hashTable->table[index].value = true;
    hashTable->table[index].isValid = true; // Mark entry as valid
}

// Add a character to the hash table
void addCharacter(HashTable* hashTable, char newChar) {
    int index = hashFunction(newChar);
    while (hashTable->table[index].isValid) { // Use linear probing for collision resolution
        index = (index + 1) % hashTable->size;
    }
    hashTable->table[index] = true;
}

// Remove a character from the hash table
void removeUniqueCharacter(HashTable* hashTable, char newChar) {
    int index = hashFunction(newChar);
    hashTable->table[index] = false;
}

char* minWindow(char* s, char* t) {
    int p_left = 0;
    int p_right = 1;

    size_t len_s = strlen(s);

    while(p_left<len_s-1){
        if (!find(s[p_left], t)){
            p_left++;
        }
    }
}