// QUESTION NAME: LC0206 Reverse Linked List

// DESCRIPTION:
// Given the head of a singly linked list, reverse the list, and return the reversed list.
//
// Input: head = [1,2,3,4,5]
// Output: [5,4,3,2,1]
//
// Input: head = [1,2]
// Output: [2,1]
//
// Input: head = []
// Output: []
//
// The number of nodes in the list is the range [0, 5000].
// -5000 <= Node.val <= 5000
//
// https://leetcode.com/problems/reverse-linked-list/

// APPROACH:
//

// FUNCTION NAME: reverseList

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "LinkedListUtils.h"

using namespace std;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr || head->next == nullptr){
            return head;
        }
        ListNode* prev = nullptr;
        ListNode* cur = head;
        ListNode* ne = head->next;

        while(ne != nullptr){
            ne = cur->next;
            cur->next = prev;
            prev = cur;
            cur = ne;
        }
        return prev;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Reverse Linked List", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, vector<int>>({
              {"T1", {1,2,3,4,5}, {5,4,3,2,1}},
              {"T2", {1}, {1}},
              {"T3", {}, {}},
      }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto head = vecToList(input);
        ListNode* resultHead = solver.reverseList(head);
        auto result = listToVec(resultHead);

        CAPTURE(result);
        CHECK(result == expected);
    }
}
