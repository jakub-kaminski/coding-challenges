// QUESTION NAME: LC0021 Reverse Linked List

// DESCRIPTION:
// You are given the heads of two sorted linked lists list1 and list2.
// Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.
//
// Input: list1 = [1,2,4], list2 = [1,3,4]
// Output: [1,1,2,3,4,4]
//
// Input: list1 = [], list2 = []
// Output: []
//
// Input: head = [1,2]
// Output: [2,1]
//
// Input: list1 = [], list2 = [0]
// Output: [0]
//
// The number of nodes in both lists is in the range [0, 50].
// -100 <= Node.val <= 100
// Both list1 and list2 are sorted in non-decreasing order.
//
// https://leetcode.com/problems/merge-two-sorted-lists/

// APPROACH:
//

// FUNCTION NAME: mergeTwoLists

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "LinkedListUtils.h"

using namespace std;


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
      if(list1 == nullptr) return list2;
      if(list2 == nullptr) return list1;

      bool flag = true;

      ListNode* res = nullptr;

      ListNode* prev1 = list1;
      ListNode* prev2 = list2;

      while(list1 != nullptr && list2 != nullptr){
         while(list1 != nullptr && list1->val <= list2->val){
             if(flag){ flag = false; res = list1;}
             prev1 = list1;
             list1 = list1->next;
         }
          if(prev1->val <= list2->val) prev1->next = list2;
          if(list1 == nullptr) break;

         while(list2 != nullptr && list2->val <= list1->val){
             if(flag){ flag = false; res = list2;}
             prev2 = list2;
             list2 = list2->next;
         }

          if(prev2->val <= list1->val) prev2->next = list1;
          if(list2 == nullptr) break;
      }
      return res;
    }
};

// Credits: KnockCat https://leetcode.com/problems/merge-two-sorted-lists/discuss/1826666/C++-oror-Easy-To-Understand-oror-2-Approaches-oror-Recursive-oror-Iterative
class SolutionRecursive {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
  {
		// if list1 happen to be NULL
		// we will simply return list2.
		if(l1 == NULL)
        {
			return l2;
		}

		// if list2 happen to be NULL
		// we will simply return list1.
		if(l2 == NULL)
        {
			return l1;
		}

		// if value pointend by l1 pointer is less than equal to value pointed by l2 pointer
		// we wall call recursively l1 -> next and whole l2 list.
		if(l1 -> val <= l2 -> val)
        {
			l1 -> next = mergeTwoLists(l1 -> next, l2);
			return l1;
		}
		// we will call recursive l1 whole list and l2 -> next
		else
        {
			l2 -> next = mergeTwoLists(l1, l2 -> next);
			return l2;
		}
	}
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge two linked lists", "[tag1]", Solution, SolutionRecursive) {
//@formatter:off
    auto [msg, list1, list2, expected] = GENERATE(table<string, vector<int>, vector<int>, vector<int>>({
           {"T1", {3,4,5}, {1,2}, {1,2,3,4,5}},
           {"T2", {1,2}, {3,4,5}, {1,2,3,4,5}},
           {"T3", {5}, {1, 2, 4}, {1,2,4,5}},
           {"T4", {1, 2, 4}, {5}, {1,2,4,5}},
           {"T5", {}, {}, {}},
           {"T6", {}, {1}, {1}},
           {"T7", {1}, {}, {1}},
           {"T8", {1}, {2}, {1,2}},
           {"T9", {2}, {1}, {1,2}},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto head1 = vecToList(list1);
        auto head2 = vecToList(list2);
        ListNode* resultHead = solver.mergeTwoLists(head1,head2);
        auto result = listToVec(resultHead);

        CAPTURE(result);
        CHECK(result == expected);
    }
}
