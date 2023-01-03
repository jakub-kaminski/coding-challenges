// QUESTION NAME: LC0141 Linked List Cycle

// DESCRIPTION:
// Given head, the head of a linked list, determine if the linked list has a cycle in it.
// There is a cycle in a linked list if there is some node in the list that can be reached again
// by continuously following the next pointer. Internally, pos is used to denote the index of the node
// that tail's next pointer is connected to. Note that pos is not passed as a parameter.
// Return true if there is a cycle in the linked list. Otherwise, return false.
//
// Input: head = [3,2,0,-4], pos = 1
// Output: true
// Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
//
// Input: head = [1,2], pos = 0
// Output: true
// Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
//
// Input: head = [1], pos = -1
// Output: false
// Explanation: There is no cycle in the linked list.
//
// The number of the nodes in the list is in the range [0, 104].
// -105 <= Node.val <= 105
// pos is -1 or a valid index in the linked-list.
//
// Can you solve it using O(1) (i.e. constant) memory?

// APPROACH:
//

// FUNCTION NAME: hasCycle

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "LinkedListUtils.h"

using namespace std;

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == nullptr) return false;

        auto fast = head;
        fast = fast->next;
        auto slow = head;
        while(fast != nullptr){
            fast = fast->next;
            if(fast != nullptr) fast=fast->next;
            else return false;
            slow = slow->next;
            if(fast == slow) return true;
        }
        return false;
    }
};

class SolutionHashMap {
public:
    bool hasCycle(ListNode *head) {
        set<ListNode*> st;
        while(head != nullptr){
            if(st.count(head)){
                return true;
            }
            else{
                st.insert(head);
            }
            head=head->next;
        }
        return false;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge two linked lists", "[tag1]", Solution) {
//@formatter:off
    auto [msg, list, expected] = GENERATE(table<string, vector<array<int,2>>, bool>({
                  {"T1", {{0,1},{0,2},{0,3},{0,-1}},false},
                  {"T2", {{0,1},{0,2},{0,3},{0,1}},true},
                  {"T3", {{0,1},{0,2},{0,3},{0,0}},true},
                  {"T4", {{0,1},{0,0}},true},
          }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto head = vecToListControlledConnections(list);
        auto result = solver.hasCycle(head);

        CAPTURE(result);
        CHECK(result == expected);
    }
}
