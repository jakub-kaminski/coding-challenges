// QUESTION NAME: LC0846 Hand Of Straights

// DESCRIPTION:
// Alice has some number of cards and she wants to rearrange the cards into groups
// so that each group is of size groupSize, and consists of groupSize consecutive cards.
//
// Given an integer array hand where hand[i] is the value written on the ith card and an
// integer groupSize, return true if she can rearrange the cards, or false otherwise.
//
// Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
// Output: true
// Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8]
//
// Input: hand = [1,2,3,4,5], groupSize = 4
// Output: false
// Explanation: Alice's hand can not be rearranged into groups of 4.
//
// 1 <= hand.length <= 10^4
// 0 <= hand[i] <= 10^9
// 1 <= groupSize <= hand.length
//
// https://leetcode.com/problems/hand-of-straights/

// APPROACH:
//

// FUNCTION NAME: isNStraightHand

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int> &hand, int groupSize) {
        int len = hand.size();
        if (len % groupSize) return false;

        sort(hand.begin(), hand.end());

        unordered_map<int, int> m;
        for (auto el: hand) {
            m[el] += 1;
        }

        int groupsToBuild = len / groupSize;

        for (int i = 0; i < len; ++i) {

            int goalCard = hand[i];
            if (!m[goalCard]) continue;

            int cardsToDo = groupSize;
            vector<int> takenCards;

            while (cardsToDo) {
                if (m.count(goalCard)) {
                    takenCards.push_back(goalCard);
                    m[goalCard] -= 1;
                    if (m[goalCard] < 1) m.erase(goalCard); // HINT: very important line, clear empty maps
                    --cardsToDo;
                    ++goalCard;
                } else {
                    for (auto el: takenCards) m[el] += 1;
                    break;
                }
            }
            if (!cardsToDo) {
                --groupsToBuild;
            }
        }

        if (!groupsToBuild) return true;
        else return false;
    }
};

// IMPLEMENTATION ENDS

vector<int> input1 = { 1,2,3,4,5 };
int groups1 = 10;
int expected1 = false;

vector<int> input2 = {1,2,3,6,2,3,4,7,8};
int groups2 = 3;
int expected2 = true;

vector<int> input3 = {9, 13, 15, 23, 22, 25, 4, 4, 29, 15, 8, 23, 12, 19, 24, 17, 18, 11, 22, 24, 17, 17, 10, 23, 21,
                      18, 14, 18, 7, 6, 3, 6, 19, 11, 16, 11, 12, 13, 8, 26, 17, 20, 13, 19, 22, 21, 27, 9, 20, 15, 20,
                      27, 8, 13, 25, 23, 22, 15, 9, 14, 20, 10, 6, 5, 14, 12, 7, 16, 21, 18, 21, 24, 23, 10, 21, 16, 18,
                      16, 18, 5, 20, 19, 20, 10, 14, 26, 2, 9, 19, 12, 28, 17, 5, 7, 25, 22, 16, 17, 21, 11};
int groups3 = 10;
int expected3 = false;

//@formatter:off
TEMPLATE_TEST_CASE("Plus One", "[tag1]", Solution) {
    auto [msg, cards, groups, expected] = GENERATE_COPY(table<string, vector<int>, int, bool>({
            {"T1", input1, groups1, expected1},
            {"T2", input2, groups2, expected2},
            {"T3", input3, groups3, expected3},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.isNStraightHand(cards, groups) == expected);
    }
}