// QUESTION NAME: LC0143 Reorder List

// DESCRIPTION:
// You are given the head of a singly linked-list. The list can be represented as:
// L0 → L1 → … → Ln - 1 → Ln
// Reorder the list to be on the following form:
// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
// https://leetcode.com/problems/reorder-list/
//
// Input: head = [1,2,3,4]
// Output: [1,4,2,3]
//
// Input: head = [1,2,3,4,5]
// Output: [1,5,2,4,3]
//
// The number of nodes in the list is in the range [1, 5 * 104].
// 1 <= Node.val <= 1000

// APPROACH:
//

// FUNCTION NAME: reorderList

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "LinkedListUtils.h"

using namespace std;


class Solution {
private:
    ListNode* reverse(int startNode, ListNode* head){
        for(int i = 0; i < startNode-1; ++i){
            head=head->next;
        }
        if(head == nullptr || head->next == nullptr){
            return head;
        }
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = head->next;

        while(curr != nullptr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
public:
    void reorderList(ListNode* head) {
        if(head->next == nullptr){
            return;
        }
        int listLen = -1;
        auto tmp = head;
        while(tmp != nullptr){
            tmp=tmp->next;
            ++listLen;
        }
        // 4 nodes: listLen=3, 3/2 = 1
        // 0 1 2 3

        // 5 nodes: listLen=4, 4/2 = 2
        // 0 1 2 3 4
        // 0 4 1 3 2

        int reverseStartPoint = listLen/2 + 1;

        ListNode* rev = reverse(reverseStartPoint, head);

        ListNode* fwd = head;
        int idx = 0;

        // 0 1 2 3 4 5
        // 0 5 1

        while(idx <= listLen/2){
            ++idx;
            auto fwdNext = fwd->next;
            auto revNext = rev->next;
            fwd->next = rev;
            rev->next = fwdNext;
            fwd = fwdNext;
            rev = revNext;
        }
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge two linked lists", "[tag1]", Solution) {
//@formatter:off
    auto [msg, list, expected] = GENERATE(table<string, vector<int>, vector<int>>({
           {"T1", {0,1,2,3,4,5},{0,5,1,4,2,3}},
           {"T1", {0,1,2,3,4},{0,4,1,3,2}},
           {"T1", {0,1,2},{0,2,1}},
           {"T1", {1},{1}},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto head = vecToList(list);
        solver.reorderList(head);
        auto result = listToVec(head);

        CAPTURE(result);
        CHECK(result == expected);
    }
}
