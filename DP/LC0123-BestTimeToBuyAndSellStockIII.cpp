// QUESTION NAME: LC0123 Best Time to Buy and Sell Stock III

// DESCRIPTION: Find the maximum profit you can achieve for given stock price.
// You may complete at most two buy&sell transactions.
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
//
// Input: prices = [3,3,5,0,0,3,1,4]
// Output: 6
// Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
// Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
//
// Input: prices = [1,2,3,4,5]
// Output: 4
// Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
// Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.
//
// Input: prices = [7,6,4,3,1]
// Output: 0
// Explanation: In this case, no transaction is done, i.e. max profit = 0.
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: maxProfit
//
#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<int> v1t;
typedef vector<vector<int>> v2t;
typedef vector<vector<vector<int>>> v3t;

struct S1 {
    int fn(int i, int canBuy, int remaining, v1t &p){
        if( i == p.size()) return 0;
        if(remaining == 0) return 0;

        int gain = 0;
        if(canBuy){
            int buy = -p[i] + fn(i+1, 0, remaining, p);
            int noBuy = 0 + fn(i+1, 1, remaining, p);
            gain = max(buy, noBuy);
        }
        else {
            int sell = p[i] + fn(i+1, 1, remaining-1, p);
            int noSell = 0 + fn(i+1, 0, remaining, p);
            gain = max(sell, noSell);
        }
        return gain;
    }

    int maxProfit(v1t p){
        int len = p.size();
        int max_transactions = 2;
        int canBuy = 1;

        return fn(0, canBuy, max_transactions, p);
    }
};

struct S2 {
    int fn(int i, int canBuy, int remaining, v1t &p, v3t &dp){
        if( i == p.size()) return 0;
        if(remaining == 0) return 0;
        if(dp[i][canBuy][remaining] != -1) return dp[i][canBuy][remaining];

        int gain = 0;
        if(canBuy){
            int buy = -p[i] + fn(i+1, 0, remaining, p, dp);
            int noBuy = 0 + fn(i+1, 1, remaining, p, dp);
            gain = max(buy, noBuy);
        }
        else {
            int sell = p[i] + fn(i+1, 1, remaining-1, p, dp);
            int noSell = 0 + fn(i+1, 0, remaining, p, dp);
            gain = max(sell, noSell);
        }
        return dp[i][canBuy][remaining] = gain;
    }

    int maxProfit(v1t p){
        int len = p.size();
        int max_transactions = 2;
        int canBuy = 1;
        v3t dp(len, v2t(2, v1t(max_transactions+1, -1)));

        return fn(0, canBuy, max_transactions, p, dp);
    }
};

struct S3 {
    int fn(int i, int canBuy, int remaining, v1t &p, v3t &dp){
        if( i == p.size()) return 0;
        if(remaining == 0) return 0;
        if(dp[i][canBuy][remaining] != -1) return dp[i][canBuy][remaining];

        int gain = 0;
        if(canBuy){
            int buy = -p[i] + fn(i+1, 0, remaining, p, dp);
            int noBuy = 0 + fn(i+1, 1, remaining, p, dp);
            gain = max(buy, noBuy);
        }
        else {
            int sell = p[i] + fn(i+1, 1, remaining-1, p, dp);
            int noSell = 0 + fn(i+1, 0, remaining, p, dp);
            gain = max(sell, noSell);
        }
        return dp[i][canBuy][remaining] = gain;
    }

    int maxProfit(v1t p){
        int len = p.size();
        int max_transactions = 2;
        v3t dp(len+1, v2t(2, v1t(max_transactions+1, 0)));

        for(int i = len-1; i >=0; --i){
            for(int canBuy = 0; canBuy <= 1; ++canBuy){
                for(int remaining = 1; remaining <= max_transactions; ++remaining){
                    int gain = 0;
                    if(canBuy){
                        int buy = -p[i] + dp[i+1][0][remaining];
                        int noBuy = 0 + dp[i+1][1][remaining];
                        gain = max(buy, noBuy);
                    }
                    else {
                        int sell = p[i] + dp[i+1][1][remaining-1];
                        int noSell = 0 + dp[i+1][0][remaining];
                        gain = max(sell, noSell);
                    }
                    dp[i][canBuy][remaining] = gain;
                }
            }
        }
        return dp[0][1][2];
//        return fn(0, canBuy, max_transactions, p, dp);
    }
};

struct S4_2DSolution{
    int fn(int i, int tr, v1t &p, v2t &dp){
        if(i == p.size() || tr == 4) return 0;
        if(dp[i][tr] != -1) return dp[i][tr];

        int action = fn(i+1, tr+1, p, dp);
        action += tr%2 ?  p[i] : -p[i];
        int hold = fn(i+1, tr, p, dp);
        return dp[i][tr] = max(action, hold);
    }
    int maxProfit(v1t &prices){
        int len = prices.size();
        v2t dp(len, v1t(4, -1));
        return fn(0, 0, prices, dp);
    }
};

struct S5_2DSolution{
    int maxProfit(v1t &prices){
        int len = prices.size();
        v2t dp(len+1, v1t(4+1, 0));
        for(int i = len-1; i >= 0; --i){
            for(int tr = 0; tr < 4; ++tr){
                int action = dp[i+1][tr+1];
                action += tr%2 ?  prices[i] : -prices[i];
                int hold = dp[i+1][tr] ;
                dp[i][tr] = max(action, hold);
            }
        }
        return dp[0][0];
    }
};

struct S6_1DSolution{
    int maxProfit(v1t &prices){
        int len = prices.size();
//        v2t dp(len+1, v1t(4+1, 0));
        v1t ahead(4+1, 0);
        v1t curr(4+1, 0);
        for(int i = len-1; i >= 0; --i){
            for(int tr = 0; tr < 4; ++tr){
                int action = ahead[tr+1];
                action += tr%2 ?  prices[i] : -prices[i];
                int hold = ahead[tr] ;
                curr[tr] = max(action, hold);
            }
            ahead = curr;
        }
        return ahead[0];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Best time to buy and sell stock III", "", S1, S2, S3, S4_2DSolution, S5_2DSolution, S6_1DSolution) {
//@formatter:off
    auto [msg, prices, expected] = GENERATE(table<string, vector<int>, int>({
        { "T1", {1,2,3,1,2,2,3}, 4 },
        { "T2", {8,1,3,1,2,2,3}, 4 },
        { "T3", {8,7,5,5,4,3,2}, 0 },
        { "T4", {8,7,5,5,2,3,2}, 1 },
        { "T5", {8,7,5,5,2,3,100,1,2,1}, 99},
        { "T6", {1, 2, 3, 1, 2, 2, 3, 1, 2, 3, 1, 2, 2, 3, 1, 2, 3, 1, 2, 2, 3,1, 2, 3, 1, 2, 2, 3}, 4
        }
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.maxProfit(prices) == expected);
    }
}
