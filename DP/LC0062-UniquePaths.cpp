// QUESTION NAME: LC0062 Unique Paths

// DESCRIPTION: Count the number of unique ways to go from top-left corner to the bottom-right corner
// Robot in a grid, no obstackles, moves DOWN or to RIGHT
// https://leetcode.com/problems/unique-paths/

// APPROACH:
// Recursion, DP, or Fibonacci property

// FUNCTION NAME: uniquePaths

//
#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>



using std::vector;
using std::string;

struct RecursiveSolution {
    int f(int r, int c, vector<vector<int>> &map) {
        if (r < 0 || c < 0) return 0;
        if (r == 0 && c == 0) return 1;

        return f(r-1, c, map) + f(r, c-1, map);
    }

    int uniquePaths(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();
        return f(r_size - 1, c_size - 1, v);
    }
};

struct MemoSolution {
    int f(int r, int c, vector<vector<int>> &map, vector<vector<int>> &dp) {
        if (r < 0 || c < 0) return 0;
        if (dp[r][c] != -1) return dp[r][c];
        if (r == 0 && c == 0) return 1;

        return dp[r][c] = f(r-1, c, map, dp) + f(r, c-1, map, dp);
    }

    int uniquePaths(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();

        vector<vector<int>> dp(r_size, vector<int>(c_size, -1));
        return f(r_size - 1, c_size - 1, v, dp);
    }
};


struct TabSolution {
    int uniquePaths(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();

        vector<vector<int>> dp(r_size, vector<int>(c_size, 0));

        for (int r = 0; r < r_size; ++r) {
            for (int c = 0; c < c_size; ++c) {
                if(r == 0 && c == 0){
                    dp[r][c] = 1;
                    continue;
                }
                if(c>0){
                    dp[r][c] += dp[r][c-1];
                }
                if(r>0){
                    dp[r][c] += dp[r-1][c];
                }
            }
        }
        return dp[r_size-1][c_size-1];
    }
};

struct SpaceOptimizedSolution {
    vector<int> uniquePaths(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();

        vector<int> dp(c_size, 0);
//        vector<vector<int>> dp(r_size, vector<int>(c_size, 0));

        for (int r = 0; r < r_size; ++r) {
            for (int c = 0; c < c_size; ++c) {
                if(c == 0) dp[0] = 1;
                if(c>0) dp[c] += dp[c-1];
            }
        }
        return dp[c_size-1];
    }
};

// LEETCODE STYLE VERSION
class Solution1 {
private:
    int rows;
    int cols;

    int fn(int r, int c, vector<vector<int>>& dp){
       if(r >= rows || c >= cols) return 0;
       if(r == rows -1 && c == cols -1) return 1;
       if(dp[r][c] != 0) return dp[r][c];

       return dp[r][c] = fn(r+1,c, dp) + fn(r, c+1, dp);
    }
public:
    int uniquePaths(int m, int n) {
        if(m == 1 && n == 1) return 1;
        rows = m;
        cols = n;

        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        return fn(0,0, dp);
    }
};


class Solution2 {
private:
    int fn(int r, int c, vector<vector<int>>& dp){
       if(r < 0 || c < 0) return 0;
       if(r == 0 && c == 0) return 1;
       if(dp[r][c] != 0) return dp[r][c];

       return dp[r][c] = fn(r-1,c, dp) + fn(r, c-1, dp);
    }
public:
    int uniquePaths(int m, int n) {
        if(m == 1 && n == 1) return 1;

        vector<vector<int>> dp(m, vector<int>(n, 0));

        return fn(m-1,n-1, dp);
    }
};


class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        for(int r = 1; r < m+1; ++r){
            for(int c = 1; c < n+1; ++c){
               if(r == 1 && c == 1) dp[r][c] = 1;
               else dp[r][c] = dp[r-1][c] + dp[r][c-1];
            }
        }

        return dp[m][n];
    }
};


// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Unique Paths", "[tag1]", SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
    vector<vector<int>> map1 = {
            {0, 0},
            {0, 0}
    };
    int result1 = 2;

    vector<vector<int>> map2 = {
            {0, 0, 0},
            {0, 0, 0}
    };
    int result2 = 3;

    vector<vector<int>> map3 = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };
    int result3 = 6;

    // 1 1 1
    // 1 2 3
    // 1 3 6
    // 1 4 10
    // 1 5
    // 1


    //@formatter:off
    auto [msg, input, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
            {"Map1", map1, result1},
            {"Map2", map2, result2},
            {"Map3", map3, result3}
    }));
    //@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.uniquePaths(input) == expected);
    }
}
