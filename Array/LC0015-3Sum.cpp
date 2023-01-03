// question name: LC0015 3Sum

// DESCRIPTION:
// Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
// such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
//
// Notice that the solution set must not contain duplicate triplets.
//
// Input: nums = [-1,0,1,2,-1,-4]
// Output: [[-1,-1,2],[-1,0,1]]
// Explanation:
// nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
// nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
// nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
// The distinct triplets are [-1,0,1] and [-1,-1,2].
// Notice that the order of the output and the order of the triplets does not matter.
//
// Input: nums = [0,1,1]
// Output: []
// Explanation: The only possible triplet does not sum up to 0.
//
// Input: nums = [0,0,0]
// Output: [[0,0,0]]
// Explanation: The only possible triplet sums up to 0.
//
// 3 <= nums.length <= 3000
// -105 <= nums[i] <= 105
//
// https://leetcode.com/problems/3sum/

// APPROACH:
//

// function name: threeSum

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        int len = nums.size();
        sort(nums.begin(),nums.end());
         vector<vector<int>> res;
         set<vector<int>> st;

        for(int bound = 2; bound < len; ++bound){
            int t = nums[bound] * (-1);
            int l = 0;
            int r = bound-1;
            while(l<r){
//                int test = nums[l]+nums[r];
//                int test_l = nums[l];
//                int test_r = nums[r];
                if(nums[l]+nums[r] == t){
                    vector<int> candidate = {nums[l], nums[r], nums[bound]};
                    if(!st.count(candidate)){
                        st.insert(candidate);
                        res.push_back(candidate);
                    }
                    ++l; --r;
                }
                else if(nums[l]+nums[r] < t) ++l;
                else --r;
            }
        }
        return res;
    }
};

class SolutionHashMap {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
      int len = nums.size();
      unordered_map<int,int> m;
      m[nums[0]]+=1;
      m[nums[1]]+=1;

      // example

      // nums[i] = -3
      // t = 3
      // el = 1
      // lookFor = 2
      //
      // nums[i] = -2
      // t = 2
      // el = 1
      // lookFor = 1
     set<vector<int>> st;
     vector<vector<int>> res;
      for(int i = 2; i < len; ++i){
         int t = nums[i] * (-1);
         for(auto& el : m){
             int lookFor = t - el.first;
             if(lookFor == el.first){
                 if(el.second > 1){ // HINT: use this instead count()
                     vector<int> c = {el.first, lookFor, nums[i]};
                     sort(c.begin(), c.end());
                     if(!st.count(c)){
                        st.insert(c);
                        res.push_back(c);
                     }
                 }
             }
             else{
                 if(m.count(lookFor) == 1){
                     vector<int> c = {el.first, lookFor, nums[i]};
                     sort(c.begin(), c.end());
                     if(!st.count(c)){
                        st.insert(c);
                        res.push_back(c);
                     }
                 }
             }
         }
         m[nums[i]]+=1;
      }
      return res;
    }
};

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("Three Sum", "[tag1]", Solution) {
TEMPLATE_TEST_CASE("Three Sum", "[tag1]", Solution, SolutionHashMap) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, vector<vector<int>>>({
            {"T1", {1,2,-3,4,-5,-6}, {{-3,1,2},{-5,1,4},{-6,2,4}}},
            {"T2", {0,0,0},{{0,0,0}}},
            {"T3", {0,0,0,0},{{0,0,0}}},
            {"T4", {-1,0,0,1,0},{{0,0,0},{-1,0,1}}},
    }));
//@formatter:on
    TestType solver;


    SECTION(msg) {
        CAPTURE(msg);

        set<vector<int>> exp;
        for(auto el : expected)
            exp.insert(el);

        auto result = solver.threeSum(input);
        set<vector<int>> res;
        for(auto el : result)
            res.insert(el);

        CAPTURE(result);
        CHECK(res == exp);
    }
}
