// QUESTION NAME: LC1463 Cherry Pickup II

// DESCRIPTION: Two robots pick cherries on a grid with cherries. They start in top left and top right corner and can only move DOWN-LEFT, DOWN, or DOWN-RIGHT. How to maximize the gain?
// Robots can occupy the same grid but collect cheries only once
//
// You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.
//
// You have two robots that can collect cherries for you:
//
// Robot #1 is located at the top-left corner (0, 0), and
// Robot #2 is located at the top-right corner (0, cols - 1).
// Return the maximum number of cherries collection using both robots by following the rules below:
//
// From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
// When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
// When both robots stay in the same cell, only one takes the cherries.
// Both robots cannot move outside of the grid at any moment.
// Both robots should reach the bottom row in grid.
//
// https://leetcode.com/problems/cherry-pickup-ii/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: cherryPickup

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>


using std::vector;
using std::string;


struct RecursiveSolution{
    int fn(int r, int c1, int c2, vector<vector<int>> &v){
        int cols = v[0].size();
        int rows = v.size();
        if(c1 < 0 || c1 >=  cols || c2 < 0 || c2 >= cols || r >= rows) return 0;

        int maxi = 0;
        for (int i = c1-1; i <= c1+1; ++i){
            for (int j = c2-1; j <= c2+1; ++j){
                maxi = std::max(maxi, fn(r+1, i, j, v));
            }
        }
        if (c1 == c2)
            return v[r][c1] + maxi;
        else
            return v[r][c1] + v[r][c2] + maxi;
    }

    int cherryPickup(vector<vector<int>> &v){
        int cols = v[0].size();
        return fn(0, 0, cols-1, v);
    }
};


typedef vector<vector<vector<int>>> v3;

struct MemoSolution{
    int fn(int r, int c1, int c2, vector<vector<int>> &v, v3 &dp){
        int cols = v[0].size();
        int rows = v.size();
        if(c1 < 0 || c1 >=  cols || c2 < 0 || c2 >= cols || r >= rows) return 0;
        if(dp[r][c1][c2] != -1) return dp[r][c1][c2];

        int maxi = 0;
        for (int i = c1-1; i <= c1+1; ++i){
            for (int j = c2-1; j <= c2+1; ++j){
                maxi = std::max(maxi, fn(r+1, i, j, v, dp));
            }
        }
        if (c1 == c2)
            return dp[r][c1][c2] = v[r][c1] + maxi;
        else
            return dp[r][c1][c2] = v[r][c1] + v[r][c2] + maxi;
    }

    // IMPORTANT INITIALIZATION
    int cherryPickup(vector<vector<int>> &v){
        int rows = v.size();
        int cols = v[0].size();
        v3 dp(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
        return fn(0, 0, cols-1, v, dp);
    }
};

// x 0 0 0 0 0 0 0 0 0 0 0 0 0 x
// x x 0 0 0 0 0 0 0 0 0 0 0 x x
// x x x 0 0 0 0 0 0 0 0 0 x x x
// x x x x 0 0 0 0 0 0 0 x x x x

//struct PersonDP{
//    v3 dp;
//    int ref = 0;
//    DP(rows){
//        for (int i = 0; i < rows; ++i)
//            vector<vector<int>> r(i+1, vector<int>());
//            dp.push_back
//
//
//    }
//};

struct MemoSolution2{
    int fn(int r, int c1, int c2, vector<vector<int>> &v, v3 &dp){
        int cols = v[0].size();
        int rows = v.size();
        if(c1 < 0 || c1 >=  cols || c2 < 0 || c2 >= cols || r >= rows) return 0;
        if(dp[r][c1][c2] != -1) return dp[r][c1][c2];

        int maxi = 0;
        for (int i = c1-1; i <= c1+1; ++i){
            for (int j = c2-1; j <= c2+1; ++j){
                maxi = std::max(maxi, fn(r+1, i, j, v, dp));
            }
        }
        if (c1 == c2)
            return dp[r][c1][c2] = v[r][c1] + maxi;
        else
            return dp[r][c1][c2] = v[r][c1] + v[r][c2] + maxi;
    }

    // IMPORTANT INITIALIZATION
    int cherryPickup(vector<vector<int>> &v){
        int rows = v.size();
        int cols = v[0].size();
        v3 dp(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
        return fn(0, 0, cols-1, v, dp);
    }
};

struct TabSolution{
    // IMPORTANT INITIALIZATION
    int cherryPickup(vector<vector<int>> &v){
        int rows = v.size();
        int cols = v[0].size();
        v3 dp(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));

        dp[0][0][cols-1] = v[0][0] +  v[0][cols-1];

        for(int r = 1; r < rows; ++r){
            for(int c1 = 0; (c1 <= r && c1 < cols); ++c1){
                for(int c2 = cols-1; (c2 >= cols-1-r && c2 >= 0); --c2){
                    int value;
                    int maxi = INT_MIN;
                    if(c1 == c2) value = v[r][c1];
                    else value = v[r][c1] + v[r][c2];
                    for(int c1p = c1-1; c1p <= c1+1; ++c1p){
                        for(int c2p = c2-1; c2p <= c2+1; ++c2p){
                            if((c1p <= r-1 && c1p < cols && c1p >= 0) &&
                               (c2p >= (rows-1)-r && c2p < cols && c2p >= 0)){
                                int valueD = dp[r-1][c1p][c2p];
                                maxi = std::max(maxi, valueD);
                            }
                        }
                    }
                    dp[r][c1][c2] = value + maxi;
                }
            }
        }
        int result = INT_MIN;
        for(auto &el : dp[rows-1]){
            for(auto &el2 : el){
                result = std::max(result, el2);
            }
        }
        return result;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", TabSolution, MemoSolution, RecursiveSolution) {
    vector<vector<int>> map1 = {
            {1, 2},
            {9, 3}
    };
    int result1 = 15;

    vector<vector<int>> map2 = {
            {1, 2, 3},
            {2, 9, 4},
            {2, 1, 9}
    };
    int result2 = (1 + 9 + 2) + (3 + 4 + 9);

    vector<vector<int>> map3 = {
            {3, 1, 1},
            {2, 5, 1},
            {1, 5, 5},
            {2, 1, 1}
    };
    int result3 = 12 + 12;

    vector<vector<int>> map4 = {
            {1, 0, 0, 0, 0, 0, 1},
            {2, 0, 0, 0, 0, 3, 0},
            {2, 0, 9, 0, 0, 0, 0},
            {0, 3, 0, 5, 4, 0, 0},
            {1, 0, 2, 3, 0, 0, 6},
    };
    int result4 = 17 + 11;


    //@formatter:off
    auto [msg, input, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
            {"Map1", map1, result1},
            {"Map2", map2, result2},
            {"Map3", map3, result3},
            {"Map4", map4, result4}
    }));
    //@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.cherryPickup(input) == expected);
    }
}
