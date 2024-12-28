// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/?envType=study-plan-v2&envId=top-interview-150

/*
Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Return the linked list sorted as well.



Example 1:


Input: head = [1,2,3,3,4,4,5]
Output: [1,2,5]
Example 2:


Input: head = [1,1,1,2,3]
Output: [2,3]


Constraints:

The number of nodes in the list is in the range [0, 300].
-100 <= Node.val <= 100
The list is guaranteed to be sorted in ascending order.
*/


 struct ListNode {
      int val;
      struct ListNode *next;
};

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct ListNode* createNode(int value){
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = value;
    node->next = NULL;
    return node;
}

struct ListNode* deleteDuplicates(struct ListNode* head) {
    if (!head){
        return NULL;
    }

    struct ListNode* dummy = createNode(0);
    dummy->next = head;

    struct ListNode* current = head;
    struct ListNode* prev = dummy;
    bool remove_current = false;

    while(current){
        int val = current->val;
        if (current->next && current->next->val == val){
            current->next = current->next->next;
            remove_current = true;
        }
        else if(remove_current){
            prev->next = current->next;
            current = current->next;
            remove_current=false;
        }
        else{
            prev = current;
            current = current->next;
        }
    }
    struct ListNode* result = dummy->next;
    free(dummy);
    return result;
}