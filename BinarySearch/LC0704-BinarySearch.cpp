// QUESTION NAME: SBS0003 Check if number exists in sorted array

// DESCRIPTION:
// Given an array of integers nums which is sorted in ascending order, and an integer target,
// write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
// You must write an algorithm with O(log n) runtime complexity.

// https://leetcode.com/problems/binary-search/

// APPROACH:
//

// FUNCTION NAME: search

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int fn(int l, int r, int t, vector<int>& nums){
        int mid = (l+r)/2;
        if(nums[mid] == t)return mid;
        else if(l<r && nums[mid]<t) return fn(mid+1,r, t, nums);
        else if(l<r && nums[mid]>t) return fn(l,mid-1, t, nums);
        return -1;
    }
    int search(vector<int>& nums, int target) {
        return fn(0, nums.size()-1, target, nums);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Implement Binary Search", "[tag1]", Solution) {
//@formatter:off
    auto [msg, v, t, expected] = GENERATE(table<string, vector<int>, int, int>({
           {"T1", {0,1,2,3,4,5,8,9}, 1, 1},
           {"T2", {0,1,2,3,4,5,8}, 8, 6},
           {"T3", {0,1,2,3,4,5,8,9}, 8, 6},
           {"T4", {0,1,2,3,4,5,8,9}, 6, -1},
           {"T5", {0,1,2,3,4,5,8,9}, 10, -1},
           {"T6", {0,1,2,3,4,5,8,9}, -3, -1},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto result = solver.search(v, t);
        CAPTURE(result);
        CHECK(result == expected);
    }
}


