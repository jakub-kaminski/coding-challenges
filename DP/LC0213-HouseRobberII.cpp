// QUESTION NAME: LC0213 House Robber

// DESCRIPTION: Pick (or "rob") non-adjacent elments of a matrix such that the sum is maximized.
// Circural array. Houses arranged in a circle
//
// Input: nums = [2,3,2]
// Output: 3
// Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
//
// Input: nums = [1,2,3,1]
// Output: 4
// Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
// Total amount you can rob = 1 + 3 = 4.
//
// Input: nums = [1,2,3]
// Output: 3
// https://leetcode.com/problems/house-robber-ii/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: rob

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
    int fn(int i, int limit, vector<int> &v, vector<int> &dp){
        if(i >= limit) return 0;
        if(dp[i] != -1) return dp[i];

        int rob = v[i] + fn(i+2, limit, v, dp);
        int noRob = fn(i+1, limit, v, dp);

        return dp[i] = max(rob, noRob);
    }
public:
    int rob(vector<int> &v) {
        if(v.size() == 1) return v[0];
        int len = v.size();

        vector<int> dp(len, -1);
        int option1 = fn(0, len-1, v, dp);

        dp.clear();
        dp = vector<int>(len, -1);

        int option2 = fn(1, len, v, dp);

        return max(option1, option2);
    }
};

//        auto dp = std::array<int, n>{-1};
//        auto dp = std::array<int, 300>{-1};
//    int dp[n];
//    memset(dp, -1, sizeof dp);

//    dp = std::vector<int> phone_book(n, -1);


// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("House Robber 1 - max sum of non-adjacent elements", "[tag1]", RecursiveMemoSolution, TabulationMemoSolution, OptimalSolution) {
TEMPLATE_TEST_CASE("House Robber 1 - max sum of non-adjacent elements", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
            {"1 house",  {1}, 1},
            {"2 houses", {1,2}, 2},
            {"3 houses middle", {1,5,2}, 5},
            {"3 houses side", {1,1,3}, 3},
            {"3 houses side", {3,1,1}, 3},
            {"3 houses sides", {3,4,2}, 4},
            {"4 houses", {2,3,1,9}, 12},
            {"5 houses", {2,3,1,9,10}, 13},
            {"5 houses", {2,10,1,3,9}, 19}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.rob(input) == expected);
    }
}
