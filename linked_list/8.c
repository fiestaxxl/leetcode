//https://leetcode.com/problems/rotate-list/description/?envType=study-plan-v2&envId=top-interview-150
/*
Given the head of a linked list, rotate the list to the right by k places.



Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]
Example 2:


Input: head = [0,1,2], k = 4
Output: [2,0,1]


Constraints:

The number of nodes in the list is in the range [0, 500].
-100 <= Node.val <= 100
0 <= k <= 2 * 109
*/


struct ListNode {
     int val;
     struct ListNode *next;
 };

#include <stdlib.h>

struct ListNode* createNode(int val){
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (!head){
        return NULL;
    }

    if (k==0){
        return head;
    }

    struct ListNode* dummy = createNode(0);
    dummy->next = head;

    struct ListNode* current = head;
    struct ListNode* prev = dummy;

    for (int i=0; i<k; i++){
        int len = 1;
        while(current->next){
            len++;
            prev = current;
            current = current->next;
        }
        k = k%len;
        if (k==0){
            struct ListNode* result = dummy->next;
            free(dummy);
            return result;
        }
        prev->next = NULL;
        current->next = dummy->next;
        dummy->next = current;
    }

    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}