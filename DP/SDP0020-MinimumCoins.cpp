// QUESTION NAME: SDP0020 Minimum Coins

// DESCRIPTION: given a collection of coins, return minimum number of coins to reach the target.
// There is infinite supply of coins of each type
// https://www.codingninjas.com/codestudio/problems/minimum-elements_3843091?leftPanelTab=0

// APPROACH:
// Recursion, DP

// FUNCTION NAME: minimumElements

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;

class Solution {
    public:
    vector<int> *cv;
    int fn(int sum){
        if(sum<0) return -1;
        if(sum==0) return 0;
        int minCoins = INT_MAX;
        bool found = false;
        for(int &c : *cv){
            int res = fn(sum-c);
            if(res > -1){
                found = true;
                minCoins = min(res, minCoins);
            }
        }
        return found ? minCoins + 1 : -1;
    }
    int minimumElements(vector<int>& coins, int sum){
        cv = & coins;
        return fn(sum);
//        int minCoins = INT_MAX;
//        for(int &c : *cv)
//            minCoins = min(fn(sum-c), minCoins);
//        return minCoins + 1;
    }
};

// 4 coins 1,2,5,10
// 6 target
// 17 coins upperbound
// coin_chosen x sum

class S2 {
    public:
    vector<int> *cv;
    unordered_map<int,int> map;
    int fn(int sum){
        if(sum<0) return INT_MAX;
        if(sum==0) return 0;
        if(map.count(sum)) return map[sum];
        int minCoins = INT_MAX;
        bool found = false;
        for(int &c : *cv){
            int res = fn(sum-c);
            if(res > -1){
                found = true;
                minCoins = min(res, minCoins);
            }
        }
        return map[sum] = found ? minCoins + 1 : -1;
    }
    int minimumElements(vector<int>& coins, int sum){
        cv = & coins;
        return fn(sum);
    }
};

class S3 {
    public:
    vector<int> *cv;
//    unordered_map<pair<int,int>, int> map;
    int minimumElements(vector<int>& coins, int sum){

//        map<pair<int,int>, int> map;
        int len = coins.size();
        int min_coin = *min_element(coins.begin(),coins.end());
        int max_num_coins = sum / min_coin + 1;
        auto dp = v2t(max_num_coins, vector<int>(sum+1, -1));
        cv = & coins;
        for(int i = 0; i < len; ++i){
            if(coins[i] <= sum) dp[0][coins[i]] = 1;
        }

        int idx = 1;
        while(dp[idx-1][sum] == -1 && idx < dp.size()){
            for(int sm = 2; sm <= sum; ++sm){
                int candidate = INT_MAX;
                for(auto &coin : coins){
                    if(sm >= coin && dp[idx-1][sm-coin] != -1){
                        candidate = min(candidate, dp[idx-1][sm-coin]);
                    }
                }
                if(candidate != INT_MAX) dp[idx][sm] = 1 + candidate;
            }
            idx++;
        }
        return dp[idx-1][sum];
    }
};

class S3b {
    public:
    vector<int> *cv;
//    unordered_map<pair<int,int>, int> map;
    int minimumElements(vector<int>& coins, int sum){
        map<pair<int,int>, int> map;
        int len = coins.size();
        int min_coin = *min_element(coins.begin(),coins.end());
        int max_num_coins = sum / min_coin + 1;
        cv = & coins;
        for(int i = 0; i < len; ++i){
//            if(coins[i] <= sum) map[(make_pair(0,coins[i]))] = 1;
            if(coins[i] <= sum) map[{0,coins[i]}] = 1;
        }

        int idx = 1;
        while(map.find(make_pair(idx-1,sum)) == map.end() && idx < max_num_coins){
            for(int sm = 2; sm <= sum; ++sm){
                int candidate = INT_MAX;
                for(auto &coin : coins){
                    if(sm >= coin && map.find(make_pair(idx-1,sm-coin)) != map.end()){
                        candidate = min(candidate, map[{idx-1,sm-coin}]);
                    }
                }
                if(candidate != INT_MAX) map[{idx,sm}] = 1 + candidate;
            }
            idx++;
        }
        if(map.find({idx-1,sum}) == map.end())
            return -1;
        else
            return map[{idx-1,sum}];
    }
};

class S4 {
    public:
    vector<int> *cv;
//    unordered_map<pair<int,int>, int> map;
    int minimumElements(vector<int>& coins, int sum){
//        map<pair<int,int>, int> map;
        int len = coins.size();
        int min_coin = *min_element(coins.begin(),coins.end());
        int max_num_coins = sum / min_coin + 1;
        auto dp = vector<int>(sum+1, -1);
        cv = & coins;
        for(int i = 0; i < len; ++i){
            if(coins[i] <= sum) dp[coins[i]] = 1;
        }

        int idx = 1;
        while(dp[sum] == -1 && idx < max_num_coins){
            for(int sm = sum; sm >= 2; --sm){
                int candidate = INT_MAX;
                for(auto &coin : coins){
                    if(sm >= coin && dp[sm-coin] != -1){
                        candidate = min(candidate, dp[sm-coin]);
                    }
                }
                if(candidate != INT_MAX) dp[sm] = 1 + candidate;
            }
            idx++;
        }
        return dp[sum];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Minimum number of coins for target sum", "[tag1]", Solution, S2, S3, S3b, S4) {
//@formatter:off
    auto [msg, input, targetSum, expected] = GENERATE(table<string, vector<int>, int, int>({
        {"T1 [expect no valid results]", {4, 5}, 7, -1},
        {"T2", {1, 2, 3}, 4, 2},
        {"T3", {1, 2, 3}, 3, 1},
        {"T4", {9, 5, 6, 1}, 11, 2},
//        {"T5 [expect recursion failure]", {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 20, 20},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.minimumElements(input, targetSum) == expected);
    }
}
