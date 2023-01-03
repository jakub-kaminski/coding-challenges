// question name: LC0645 Set Mismatch

// DESCRIPTION:
// Input: nums = [1,2,2,4]
// Output: [2,3]
//
// https://leetcode.com/problems/set-mismatch/

// APPROACH:
//

// function name: minwindow

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
       unordered_map<int,int> umap;
       int duplicate = 0;
       int missing = 0;
       for(auto& el : nums){
           if(umap.count(el) > 0){
               duplicate = el;
           }
           umap[el] += 1;
       }
        for(int i = 1; i <= nums.size(); ++i){
           if(umap.count(i) == 0){
               missing = i;
               break;
           }

        }
        return {duplicate, missing};
    }
};

class Solution2 {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        unordered_map<int,int> umap;
        int duplicate = 0;
        int sum = 0;
        for(auto& el : nums){
            if(umap.count(el) > 0){
                duplicate = el;
            }
            umap[el] += 1;
            sum += el;
        }
        int idealSum = ((1 + nums.size())*nums.size()) / 2;

        // idealSum = sum - duplicate + missing
        int missing = idealSum + duplicate - sum;

        return {duplicate, missing};
    }
};


// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Set Mismatch", "[tag1]", Solution, Solution2) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, vector<int>>({
          {"T1", {1,2,2,4}, {2,3}},
          {"T2", {1,2,3,2,4}, {2,5}},
          {"T3", {1,1}, {1,2}},
  }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.findErrorNums(input);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
