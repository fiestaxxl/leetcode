//https://leetcode.com/problems/longest-substring-without-repeating-characters/?envType=study-plan-v2&envId=top-interview-150

/*
Given a string s, find the length of the longest
substring without repeating characters.

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_CHARACTERS 256 // Assuming ASCII characters

// Hash table structure
typedef struct {
    bool* table;
} HashTable;

// Initialize the hash table
HashTable* initHashTable() {
    HashTable* hashtable = malloc(sizeof(HashTable));
    hashtable->table = calloc(MAX_CHARACTERS, sizeof(bool));
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        hashtable->table[i] = false;  // All characters are initially not present
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

// Add a character to the hash table
void addUniqueCharacter(HashTable* hashTable, char newChar) {
    int index = hashFunction(newChar);
    hashTable->table[index] = true;
}

// Remove a character from the hash table
void removeUniqueCharacter(HashTable* hashTable, char newChar) {
    int index = hashFunction(newChar);
    hashTable->table[index] = false;
}

int max(int a, int b) {
    if (a>=b) {
        return a;
    }
    else return b;
}

int lengthOfLongestSubstring(char* s) {
    size_t len_s = strlen(s);

    if (len_s==0) {
        return 0;
    }


    int p_left = 0;
    int p_right = 1;
    int curr_length = 1;
    int max_length = 1;

    HashTable* hashtable = initHashTable();

    addUniqueCharacter(hashtable, s[p_left]);

    while (p_left<len_s-1){
        if (isUnique(hashtable, s[p_right])){
            addUniqueCharacter(hashtable, s[p_right]);
            curr_length++;
            max_length = max(max_length, curr_length);

            if (p_right<len_s-1){
                p_right++;
            }

        }
        else {
            removeUniqueCharacter(hashtable, s[p_left]);
            curr_length--;
            max_length = max(max_length, curr_length);
            p_left++;
        }
    }

    freeHashTable(hashtable);
    return max_length;
}

int main(){
    char a[] = " ";
    int res = lengthOfLongestSubstring(a);
    printf("RESULT IS %d\n", res);
    return 0;
}