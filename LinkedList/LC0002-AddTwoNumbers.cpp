// QUESTION NAME: LC0002 Add Two Numbers

// DESCRIPTION:
// You are given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order, and each of their nodes contains a single digit.
// Add the two numbers and return the sum as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//
// Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [7,0,8]
// Explanation: 342 + 465 = 807.
//
// Input: l1 = [0], l2 = [0]
// Output: [0]
//
// Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
// Output: [8,9,9,9,0,0,0,1]
//
// The number of nodes in each linked list is in the range [1, 100].
// 0 <= Node.val <= 9
// It is guaranteed that the list represents a number that does not have leading zeros.
//
// https://leetcode.com/problems/add-two-numbers/

// APPROACH:
//

// FUNCTION NAME: addTwoNumbers

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "LinkedListUtils.h"

using namespace std;

class Solution {
private:
    void fn(ListNode* l1, ListNode* l2, ListNode* res, int carry){
        if(l1 == nullptr && l2 == nullptr && carry == 0) return;
        if(l1 == nullptr && l2 == nullptr && carry == 1){
            res->next = new ListNode(1);
            return;
        };

        if(l1 == nullptr && l2 != nullptr){
            int val = (carry + l2->val);
            if(val >= 10){carry = 1; val = val % 10;}
            else{carry = 0;}
            res->next = new ListNode(val);
            fn(l1, l2->next, res->next, carry);
            return;
        }

        if(l1 != nullptr && l2 == nullptr){
            int val = (carry + l1->val);
            if(val >= 10){carry = 1; val = val % 10;}
            else{carry = 0;}
            res->next = new ListNode(val);
            fn(l1->next, l2, res->next, carry);
            return;
        }

        int val = (carry + l1->val + l2->val);
        if(val >= 10){carry = 1; val = val % 10;}
        else{carry = 0;}
        res->next = new ListNode(val);
        fn(l1->next, l2->next, res->next, carry);
        return;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res = new ListNode(0);
        fn(l1,l2,res,0);
        return res->next;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge two linked lists", "[tag1]", Solution) {
//@formatter:off

    auto [msg, list1, list2, expected] = GENERATE(table<string, vector<int>, vector<int>, vector<int>>({
           {"T1", {9,9,9,9,9,9,9}, {9,9,9,9}, {8,9,9,9,0,0,0,1}},
           {"T2", {2,4,3}, {5,6,4}, {7,0,8}},
           {"T3", {0}, {0}, {0}},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto head1 = vecToList(list1);
        auto head2 = vecToList(list2);
        ListNode* resultHead = solver.addTwoNumbers(head1,head2);
        auto result = listToVec(resultHead);

        CAPTURE(result);
        CHECK(result == expected);
    }
}
