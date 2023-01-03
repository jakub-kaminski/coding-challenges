// QUESTION NAME: SDP0022 Ways to Make Coin Change

// DESCRIPTION: given a collection of coins, return the numer of ways coins can be chosen to reach.
// The order of choosing coins does not matter. There is infinite supply of coins of each type
// https://www.codingninjas.com/codestudio/problems/ways-to-make-coin-change_630471

// APPROACH:
// Recursion, DP

// FUNCTION NAME: countWaysToMakeChange

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;

class Solution {
    public:
    vector<int> *cv;
    int fn(int idx, int sum){
        if(sum<0 || idx < 0) return 0;
        if(sum==0) return 1;
        int take = 0;
        if(sum >= (*cv)[idx])
            take = fn(idx, sum-(*cv)[idx]);
        int shift = fn(idx-1, sum);
        return take + shift;
    }
    int countWaysToMakeChange(vector<int>& coins, int sum){
        if(sum < 1) return 0;
        int len = coins.size();
        cv = & coins;
        return fn(len-1,sum);
    }
};

class S2 {
    public:
    map<pair<int,int>,int> m;
    vector<int> *cv;
    int fn(int idx, int sum){
        if(sum<0 || idx < 0) return 0;
        if(sum==0) return 1;
//        if(idx==0) return sum%(*cv)[0]==0;
        if(m.count({idx,sum})) return m[{idx,sum}];
        int take = 0;
        if(sum >= (*cv)[idx])
            take = fn(idx, sum-(*cv)[idx]);
        int shift = fn(idx-1, sum);
        return m[{idx,sum}] = take + shift;
    }
    int countWaysToMakeChange(vector<int>& coins, int sum){
        if(sum < 1) return 0;
        int len = coins.size();
        cv = & coins;
        return fn(len-1,sum);
    }
};

typedef vector<vector<int>> v2t;
//class S3 {
//    public:
//    int countWaysToMakeChange(vector<int>& coins, int sum) {
//        int len = coins.size();
//        vector<vector<int>> dp(len-1, vector<int>(sum+1, 0));
//        for(int i = coins[0]; i <= sum; i+=coins[0]) dp[0][i] = 1;
////        for(int i = 0; i < len; ++i) dp[i][0] = 1;
//
//        for(int idx = 1; idx < len; ++idx){
//            for(int s = 2; s <= sum; s+=coins[idx]) {
//                dp[idx-1][0] = 1;
//                if(s>=coins[idx]){
//                    dp[idx][]
//                }
//            }
//        }
//
//    }
//};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Number of ways to reach target sum given coin types", "[tag1]", Solution, S2) {
//@formatter:off
    auto [msg, input, targetSum, expected] = GENERATE(table<string, vector<int>, int, int>({
        { "test0 [expect no valid results]", {4, 5}, 0, 0 },
        { "test0b [expect no valid results]", {4, 5}, 6, 0 },
        { "test0c [expect no valid results]", {4, 5}, 3, 0 },
        { "test0c [expect no valid results]", {4, 6}, 5, 0 },
        { "test1", {1, 2, 3}, 4, 4 },
        { "test2", {1, 2, 3}, 2, 2 },
        { "test3", {9, 5, 6, 1}, 11, 6 },
        { "test3b", {1, 5, 6, 9}, 11, 6 },
        { "test3c", {9, 1, 6, 5}, 11, 6 },
        { "test4", {1, 2, 3, 4}, 3, 3 },
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.countWaysToMakeChange(input, targetSum) == expected);
    }
}
