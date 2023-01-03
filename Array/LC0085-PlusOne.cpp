// QUESTION NAME: LC0066 Plus One

// DESCRIPTION:
// You are given a large integer represented as an integer array digits,
// where each digits[i] is the ith digit of the integer.
// The digits are ordered from most significant to least significant
// in left-to-right order. The large integer does not contain any leading 0's.
//
// Input: digits = [1,2,3]
// Output: [1,2,4]
// Explanation: The array represents the integer 123.
// Incrementing by one gives 123 + 1 = 124.
// Thus, the result should be [1,2,4].
//
// Input: digits = [4,3,2,1]
// Output: [4,3,2,2]
// Explanation: The array represents the integer 4321.
// Incrementing by one gives 4321 + 1 = 4322.
// Thus, the result should be [4,3,2,2].
//
// Input: digits = [9]
// Output: [1,0]
// Explanation: The array represents the integer 9.
// Incrementing by one gives 9 + 1 = 10.
// Thus, the result should be [1,0].
//
// 1 <= digits.length <= 100
// 0 <= digits[i] <= 9
// digits does not contain any leading 0's.
//
// https://leetcode.com/problems/plus-one/

// APPROACH:
//

// FUNCTION NAME: plusOne

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;


class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
      int len = digits.size();
      auto res = digits;
      res[len-1] += 1;
      for(int i = len-1; i >= 0; --i) {
         if(i == 0 && res[i] == 10){
             res[i] = 0;
             vector<int> tmp = {1};
             tmp.insert(tmp.end(), res.begin(), res.end());
             return tmp;
         }
         if(i > 0 && res[i] == 10){
            res[i] = 0;
            res[i-1] += 1;
         }
         else return res;
      }
      return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Plus One", "[tag1]", Solution) {
    auto [msg, cost, expected] = GENERATE(table<string, vector<int>, vector<int>>({
              {"T1", {0}, {1}},
              {"T2", {8}, {9}},
              {"T3", {1,9}, {2,0}},
              {"T4", {9}, {1,0}},
              {"T5", {9,9}, {1,0,0}},
              {"T6", {9,9,0,9,9}, {9,9,1,0,0}},
      }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.plusOne(cost) == expected);
    }
}
