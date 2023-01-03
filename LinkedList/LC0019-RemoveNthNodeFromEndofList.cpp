// QUESTION NAME: LC0019 Remove Nth Node From End of List

// DESCRIPTION:
// Given the head of a linked list, remove the nth node from the end of the list and return its head.
//
// Input: head = [1,2,3,4,5], n = 2
// Output: [1,2,3,5]
//
// Input: head = [1], n = 1
// Output: []
//
// Input: head = [1,2], n = 1
// Output: [1]
//
// The number of nodes in the list is sz.
// 1 <= sz <= 30
// 0 <= Node.val <= 100
// 1 <= n <= sz
//
// Follow up: Could you do this in one pass?
//
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

// APPROACH:
// Dummy Head and List Offset

// FUNCTION NAME: removeNthFromEnd

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>
#include "LinkedListUtils.h"

using namespace std;


class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
         if(head->next == nullptr) return nullptr;

         ListNode* dummy = new ListNode();
         dummy->next = head;

         ListNode* ahead = dummy;

         for(int i = 0; i < n; i++) ahead=ahead->next;

         ListNode* curr = dummy;

         while(ahead != nullptr && ahead->next !=nullptr){
             ahead=ahead->next;
             curr=curr->next;
         }
         curr->next = curr->next->next;

        return dummy->next;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Remove Nth from end of linekd list", "[tag1]", Solution) {
//@formatter:off

    auto [msg, list1, k, expected] = GENERATE(table<string, vector<int>, int, vector<int>>({
           {"T1", {1,2,3,4,5}, 1, {1,2,3,4}},
           {"T2", {1,2,3,4,5}, 2, {1,2,3,5}},
           {"T3", {1,2,3,4,5}, 3, {1,2,4,5}},
           {"T4", {1,2,3,4,5}, 4, {1,3,4,5}},
           {"T5", {1,2,3,4,5}, 5, {2,3,4,5}},
           {"T6", {1,2}, 1, {1}},
           {"T7", {1,2}, 2, {2}},
           {"T8", {1}, 1, {}},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto head1 = vecToList(list1);
        ListNode* resultHead = solver.removeNthFromEnd(head1,k);
        auto result = listToVec(resultHead);

        CAPTURE(result);
        CHECK(result == expected);
    }
}
