//https://leetcode.com/problems/lru-cache/description/?envType=study-plan-v2&envId=top-interview-150

/*
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.



Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4


Constraints:

1 <= capacity <= 3000
0 <= key <= 104
0 <= value <= 105
At most 2 * 105 calls will be made to get and put.
*/


#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    int val;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int key, int value){
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = value;
    node->key = key;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void moveToHead(Node* node, Node* head){
    //detach node from current pos
    node->prev->next = node->next;
    node->next->prev = node->prev;

    //move node after head
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
}

Node* removeFromTail(Node* tail){
    Node* node = tail->prev;
    node->prev->next = tail;
    tail->prev = node->prev;
    return node;
}

typedef struct {
    Node* head;
    Node* tail;
    Node** table;
    int capacity;
    int size;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->head = createNode(0,0);
    cache->tail = createNode(0,0);
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;

    cache->table = (Node**)calloc(10001, sizeof(Node*));

    cache->capacity = capacity;
    cache->size = 0;
    return cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node* node = obj->table[key];

    if (node==NULL){
        return -1;
    }

    moveToHead(node, obj->head);
    return node->val;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node* node = obj->table[key];

    if (node!=NULL){
        node->val = value;
        moveToHead(node, obj->head);
    }
    else {
        Node* newNode = createNode(key, value);
        newNode->prev = obj->head;
        newNode->next = obj->head->next;
        obj->head->next->prev = newNode;
        obj->head->next = newNode;
        obj->table[key] = newNode;
        obj->size++;
    }

    if (obj->capacity<obj->size){
        Node* node = removeFromTail(obj->tail);
        obj->table[node->key] = NULL;
        free(node);
        obj->size--;
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node* current = obj->head;
    while(current){
        Node* next = current->next;
        free(current);
        current = next;
    }

    free(obj->table);
    free(obj);
}
