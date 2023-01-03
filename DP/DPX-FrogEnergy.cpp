// QUESTION NAME: DPX-Frog Minimum energy
// DESCRIPTION: frog jums on stones of different heights.
// The energy cost of jums is expressed as abs|h(i+1) - h(i)| or abs|h(i+2) - h(i)|
// Becasue frog can jump one or two stones.
// Compute the minimum energy cost to jump to the last stone

// APPROACH:
// Recursion, DP

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using std::string;
using std::vector;

struct RecursiveSolution {
    int f(int ind, vector<int> &heights){
        if(ind == 0) return 0;

        int left_tree = f(ind-1, heights) + abs(heights[ind] - heights[ind-1]);
        int right_tree = INT_MAX;
        if(ind >= 2) right_tree = f(ind-2, heights) + abs(heights[ind] - heights[ind-2]);
        return std::min(left_tree, right_tree);
    }

    int solve(vector<int> heights) {
        int ind = heights.size() -1;
        return f(ind, heights);
    }
};


struct RecursiveMemoSolution {
    int f(int ind, vector<int> &heights, vector<int> &dp){
        if(ind == 0) return 0;
        if(dp[ind] != -1) return dp[ind];

        int left_tree = f(ind-1, heights, dp) + abs(heights[ind] - heights[ind-1]);
        int right_tree = INT_MAX;
        if(ind >= 2) right_tree = f(ind-2, heights, dp) + abs(heights[ind] - heights[ind-2]);
        dp[ind] = std::min(left_tree, right_tree);
        return dp[ind];
    }

    int solve(vector<int> heights) {
        int len = heights.size();
        vector<int> dp(len,-1);
        return f(len-1, heights, dp);
    }
};



struct SpaceOptimizedDPSolution {

    int solve(vector<int> heights) {
        int len = heights.size();
        if(len <= 1) return 0;

        int prev = 0;
        int prev2 = 0;

        for(int i = 1; i < len; ++i){
            int a = prev + abs(heights[i] - heights[i-1]);
            int b = INT_MAX;
            if (i > 1) b = prev2 + abs(heights[i] - heights[i-2]);
            int cur = std::min(a, b);
            prev2 = prev;
            prev = cur;
        }
        return prev;
    }
};


struct TabulationMemoSolution {
    int f(int ind, vector<int> &heights, vector<int> &dp){
    }

    int solve(vector<int> heights) {
        int len = heights.size();
        vector<int> dp(len,0);
        if(len <= 1) return 0;

        for(int i = 1; i < len; ++i){
            int left = dp[i-1] + abs(heights[i] - heights[i-1]);
            int right = INT_MAX;
            if (i > 1) right = dp[i-2] + abs(heights[i] - heights[i-2]);
            dp[i] = std::min(left, right);
        }
        return dp[len-1];
    }
};

struct OptimalSolution {
    int solve(int n) {
        if(n == 1) return 0;
        if(n == 2) return 1;

        int prev2 = 0;
        int prev1 = 1;
        for(int i = 2; i < n; ++i){
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Frog Energy", "[tag1]", SpaceOptimizedDPSolution, RecursiveSolution, RecursiveMemoSolution, TabulationMemoSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
            {"Two locations",  {0,10}, 10},
            {"Three locations, min cost possible",  {0,10,0}, 0},
            {"Three locations, ascending",  {0,10,20}, 20},
            {"Three locations, flat",  {0,10,10}, 10},
            {"Four locations",  {0,20,0,10}, 10},
            {"Six locations, challenge greedy",  {30,10,60,10,60,50}, 40}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(input) == expected);
    }
}
