// QUESTION NAME: LC0219 Contains Duplicate II

//Given an integer array nums and an integer k, return true
// if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.

// https://leetcode.com/problems/contains-duplicate-ii/

// APPROACH: Hash Map + Make sure to update of existing key when condition not met
//

// FUNCTION NAME: containsNearbyDuplicate

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_map<int, int> umap;

        for (int i = 0; i < nums.size(); ++i) {
            if (umap.count(nums[i]) && (abs(i - umap[nums[i]]) <= k))
                return true;
            umap[nums[i]] = i;
        }
        return false;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Contains Duplicate II", "[tag1]", Solution) {
//@formatter:off
auto [msg, input, k, expected] = GENERATE_COPY(table<string, vector<int>, int, bool>({
        {"T1:", {1,2,3,4,1}, 2, false},
        {"T2:", {1,2,1,4,1}, 1, false},
        {"T3:", {1,2,1,4,1}, 2, true},
        {"T4:", {1,2,3,4,1}, 4, true}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.containsNearbyDuplicate(input, k);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
