/// QUESTION NAME: LC0238 Product of Array Except Self

// DESCRIPTION:
// Given an integer array nums, return an array answer such that answer[i]
// is equal to the product of all the elements of nums except nums[i].
// The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
// You must write an algorithm that runs in O(n) time and without using the division operation.
//
// Input: nums = [1,2,3,4]
// Output: [24,12,8,6]
//
// Input: nums = [-1,1,0,-3,3]
// Output: [0,0,9,0,0]
//
// 2 <= nums.length <= 105
// -30 <= nums[i] <= 30
// The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
// Follow up: Can you solve the problem in O(1) extra space complexity?
// (The output array does not count as extra space for space complexity analysis.)

// APPROACH:
//

// FUNCTION NAME: isPalindrome

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int> &v) const {
        if (v.empty()) return 0;
        if (v.size() == 1) return v[0];

        int len = v.size();
        int max = v[0];
        int sum = 0;

        for (int i = 0; i < len; i++) {
            sum += v[i];
            if (sum > max) {
                max = sum;
            }
            if (sum < 0) {
                sum = 0;
//            continue;
            }
        }
        return max;
    }
};

//struct ReturnSubarraySolution {
//    std::vector<int> solve(in_type &vec) const;
// std::vector<int> ReturnSubarraySolution::solve(in_type &v) const {
//    if( v.empty()) return {};
//    if( v.size() == 1) return v;
//
//    int len = v.size();
//    int max = v[0];
//    int sum = 0;
//
//    int head = 0;
//    int tail = 0;
//
//    int best_head = 0;
//    int best_tail = 0;
//
//    for(int i = 0; i < len; i++){
//        sum += v[i];
//        if(sum > max){
//            max = sum;
//            head = i;
//            best_head = head;
//            best_tail = tail;
//        }
//        if(sum < 0){
//            tail = i+1; //TODO
//            sum = 0;
////            continue;
//        }
//    }
//    // Credits: https://stackoverflow.com/a/58724503
//    return {v.begin() + best_tail, v.begin() + best_head + 1};
//}
//};

TEMPLATE_TEST_CASE("Get max sum of subarray: Kadane's Algorithm", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
            {"1 Element",  {3}, 3},
            {"2 Elements",  {2, 1}, 3},
            {"Many elements with negative values", {-2,1,-3,4,-1,2,1,-5,4}, 6},
            {"A few elements, single negative value",  {5,4,-1,7,8}, 23},
            {"A few negative values",  {-3,-2,-1,-4,-5}, -1}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        INFO("Description of current input: " << msg);
        CAPTURE(msg);
        CHECK(solver.maxSubArray(input) == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

// IMPLEMENTATION ENDS

}

//TEMPLATE_TEST_CASE("Max subarray: Kadane's Algorithm", "[tag1]", ReturnSubarraySolution) {
////@formatter:off
//    auto [msg, input, expected] = GENERATE(table<string, in_type, out2_type>({
//        {"1 Element",  {3}, {3}},
//        {"2 Elements",  {2, 1}, {2,1}},
//        {"Many elements with negative values", {-2,1,-3,4,-1,2,1,-5,4}, {4,-1,2,1}},
//        {"A few elements, single negative value",  {5,4,-1,7,8}, {5,4,-1,7,8}},
//        {"A few negative values",  {-3,-2,-1,-4,-5}, {-1}},
//        {"Many equal elements with negative values", {-3, -3, -3, -3, -3, -3, -3, -3, -3 }, {-3}},
//        {"Many elements with negative values and single larger negative value", {-3, -3, -3, -3, -3, -2, -3, -3, -3 }, {-2}}
//    }));
////@formatter:on
//    TestType solver;
//
//    SECTION(msg) {
//        INFO("[Kadane's] Subarray: " << msg);
//        CAPTURE(msg);
//        CHECK(solver.solve(input) == expected);
//    }
//}
