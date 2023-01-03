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
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        if (l1->val <= l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return nullptr; // HINT: Remember both {{}} and {} inputs
        while (lists.size() > 1) {
            int i = 0;
            vector<ListNode *> tmp{};
            // size 3:
            // i: 0..1, 2
            while (i < lists.size() - 1) {
                //            auto twoMerged = mergeTwoLists(vPtr->at(i),vPtr->at(i+1));
                auto twoMerged = mergeTwoLists(lists[i], lists[i + 1]);
                tmp.push_back(twoMerged);
                i += 2;
            }
            auto lastList = lists.back();
            int listsSize = lists.size();
            lists = tmp;

            if (listsSize % 2) {
                lists.push_back(lastList);
            }

//            if(i == listsSize-1){ // ALTERNATIVE
//                lists.push_back(lastList);
//            }
        }
        return lists[0];
    }
};


// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge k sorted linked lists", "[tag1]", Solution) {
//@formatter:off
    auto [msg, vecList, expected] = GENERATE(table<string, vector<vector<int>>, vector<int>>({
           {"T1", {{3,4,5}, {1,2}}, {1,2,3,4,5}},
           {"T2", {{1,2}, {3,4,5}}, {1,2,3,4,5}},
           {"T3", {{5}, {1, 2, 4}}, {1,2,4,5}},
           {"T4", {{1, 2, 4}, {5}}, {1,2,4,5}},
           {"T5", {{}, {}}, {}},
           {"T6", {{}, {1}}, {1}},
           {"T7", {{1}, {}}, {1}},
           {"T8", {{1}, {2}}, {1,2}},
           {"T9", {{2}, {1}}, {1,2}},
           {"T10", {{3,4,5}, {1,2}, {8,9}, {0,6,7}}, {0,1,2,3,4,5,6,7,8,9}},
           {"T11", {{1,2}, {3,4,5}, {0,6}}, {0,1,2,3,4,5,6}},
           {"T12", {{5}, {1, 2, 4}, {-2,0}}, {-2,0,1,2,4,5}},
           {"T13", {{1, 2, 4}, {5},{3, 8}}, {1,2,3,4,5,8}},
           {"T14", {{}, {}}, {}},
           {"T15", {{}, {1}, {}, {}}, {1}},
           {"T16", {{1}, {}, {}, {0}}, {0,1}},
           {"T17", {{1}, {2}, {1}, {1}}, {1,1,1,2}},
           {"T18", {{2}, {1}, {0,3}}, {0,1,2,3}},
           {"T19", {{}}, {}},
           {"T20", {}, {}},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        vector<ListNode *> input;
        input.reserve(vecList.size());
        for (auto &vec: vecList) {
            auto tmp = vecToList(vec);
            input.push_back(tmp);
        }
        ListNode *resultHead = solver.mergeKLists(input);
        auto result = listToVec(resultHead);

        CAPTURE(result);
        CHECK(result == expected);
    }
}

