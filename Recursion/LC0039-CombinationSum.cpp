// QUESTION NAME: LC0039 Combination Sum

// DESCRIPTION: Count the number of unique ways to climb stairs
// Given an array of distinct integers candidates and a target integer target,
// return a list of all unique combinations of candidates where the chosen
// numbers sum to target. You may return the combinations in any order.
//
// The same number may be chosen from candidates an unlimited number of times.
// Two combinations are unique if the frequency of at least one of the chosen numbers is different.
//
// The test cases are generated such that the number of unique combinations
// that sum up to target is less than 150 combinations for the given input.
//
// Input: candidates = [2,3,6,7], target = 7
// Output: [[2,2,3],[7]]
// Explanation:
// 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
// 7 is a candidate, and 7 = 7.
// These are the only two combinations.
//
// Input: candidates = [2,3,5], target = 8
// Output: [[2,2,2,2],[2,3,3],[3,5]]
//
// Input: candidates = [2], target = 1
// Output: []
//
// 1 <= candidates.length <= 30
// 2 <= candidates[i] <= 40
// All elements of candidates are distinct.
// 1 <= target <= 40

// APPROACH:
// Hashmaps

// FUNCTION NAME: https://leetcode.com/problems/combination-sum/

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
    void fn(int i, int sum, int target, vector<int>& c, vector<vector<int>>& allRes, vector<int>& resNow){
        if(sum == target){
              allRes.push_back(resNow);
          return;
        }
        if(i == c.size() || sum + c[i] > target) return;

        fn(i+1, sum, target, c, allRes, resNow); // not take
        resNow.push_back(c[i]);
        fn(i, sum+c[i], target, c, allRes, resNow); // take and stay
        //fn(i+1, sum+c[i], target, c, allRes, resNow,st); // HINT: this leads to duplicated results. Use simpler actions
        resNow.pop_back();
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> allRes;
        vector<int> resNow;
        fn(0, 0, target, candidates, allRes, resNow);
        return allRes;
    }
};

// IMPLEMENTATION ENDS

template <typename T1, typename T2> bool verify(T1 a, T2 b) {
    set<T2> setA; set<T2> setB;
    for(T2& ela : a) setA.insert(ela);
    for(T2& elb : b) setB.insert(elb);

    return setA == setB;
}

template <typename T1, typename T2>
set<T2> makeSet(T1 a) {
    set<T2> setA;
    for(T2 ela : a) setA.insert(ela);
    return setA;
}

TEMPLATE_TEST_CASE("DFS", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, target, expected] = GENERATE(table<string, vector<int>, int, vector<vector<int>>>({
             {"T1:", {2,3,6,7}, 7, {{2,2,3},{7}}},
             {"T2:", {2,3,5}, 8, {{2,2,2,2},{2,3,3},{3,5}}},
             {"T3:", {2}, 1, {}},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.combinationSum(input, target);
        auto resultSet = makeSet<vector<vector<int>>, vector<int>>(result);
        auto expectedSet = makeSet<vector<vector<int>>, vector<int>>(expected);
        CAPTURE(result);
        CHECK(resultSet == expectedSet);
    }
}
