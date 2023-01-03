/// QUESTION NAME: LC1046 Last Stone Weight

// DESCRIPTION:
// You are given an array of integers stones where stones[i] is the weight of the ith stone.
// We are playing a game with the stones. On each turn, we choose the heaviest
// two stones and smash them together. Suppose the heaviest two stones
// have weights x and y with x <= y. The result of this smash is:
// If x == y, both stones are destroyed, and
// If x != y, the stone of weight x is destroyed,
// and the stone of weight y has new weight y - x.
//
// At the end of the game, there is at most one stone left.
// Return the weight of the last remaining stone. If there are no stones left, return 0.
//
// Input: stones = [2,7,4,1,8,1]
// Output: 1
// Explanation:
// We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
// we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
// we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
// we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.
//
// Input: stones = [1]
// Output: 1
//
// 1 <= stones.length <= 30
// 1 <= stones[i] <= 1000

// APPROACH:
//

// FUNCTION NAME: lastStoneWeight

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int fn(int l, int r, int k, vector<int> &v) {
        int pivot = v[r];
        int p = l;
        for (int i = l; i < r; ++i) {
            if (v[i] <= pivot) {
                swap(v[i], v[p]);
                p += 1;
            }
        }
        swap(v[p], v[r]);
        if (p > k) return fn(l, p - 1, k, v);
        if (p < k) return fn(p + 1, r, k, v);
        if (p == k) return v[p];
        return 0;
    }


    int quickSelect(vector<int> &v, int k) {
        int len = v.size();
        return fn(0, len - 1, k, v);
    }

    int lastStoneWeight(vector<int> &stones) {
        while (stones.size() > 1) {
            int len = stones.size();
            int st1 = quickSelect(stones, len - 1);
            int st2 = quickSelect(stones, len - 2);
            stones.pop_back();
            stones.pop_back();
            if (st1 != st2) stones.push_back(abs(st1 - st2));
        }

        if (stones.size() == 1) return stones[0];
        else return 0;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Last Stone Weight", "[tag1]", Solution) {
//@formatter:off
auto [msg, stones, expected] = GENERATE(table<string, vector<int>, int>({
           {"T1",  {2,7,4,1,8,1}, 1},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.lastStoneWeight(stones) == expected);
    }
}