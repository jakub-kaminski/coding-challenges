// QUESTION NAME: SDP0032 Subsequence Counting

// DESCRIPTION: given two strings, return the number of ways a subsequence from s1 can be formed such that it creates s2.
// https://www.codingninjas.com/codestudio/problems/subsequence-counting_3755256

// APPROACH:
// Recursion, DP

// FUNCTION NAME: subsequenceCounting

#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;


class Solution {
public:
    int fn(int i1, int i2, string &s1, string &s2) {
        if (i2 < 0) return 1;
        if (i1 < 0) return 0;

        int move = 0;
        if (s1[i1] == s2[i2]) {
            move = fn(i1 - 1, i2 - 1, s1, s2);
        }
        int stay = fn(i1 - 1, i2, s1, s2);
        return move + stay;
    }


    int subsequenceCounting(string s1, string s2) {
        int i1 = s1.size();
        int i2 = s2.size();

        return fn(i1 - 1, i2 - 1, s1, s2);
    }
};

typedef vector<vector<int>> v2t;

class S2 {
public:
    int fn(int i1, int i2, string &s1, string &s2, v2t &dp) {
        if (i2 < 0) return 1;
        if (i1 < 0) return 0;
        if (dp[i1][i2] != -1) return dp[i1][i2];

        int move = 0;
        if (s1[i1] == s2[i2]) {
            move = fn(i1 - 1, i2 - 1, s1, s2, dp);
        }
        int stay = fn(i1 - 1, i2, s1, s2, dp);
        return dp[i1][i2] = move + stay;
    }

    int subsequenceCounting(string s1, string s2) {
        int i1 = s1.size();
        int i2 = s2.size();

        v2t dp(i1, vector<int>(i2, -1));

        return fn(i1 - 1, i2 - 1, s1, s2, dp);
    }
};

class S3 {
public:
//    int fn(int i1, int i2, string &s1, string &s2, v2t &dp){
//        if(i2 < 0) return 1;
//        if(i1 < 0) return 0;
//        if(dp[i1][i2] != -1) return dp[i1][i2];
//
//        int move = 0;
//        if(s1[i1] == s2[i2]){
//            move = fn(i1-1, i2-1, s1, s2, dp);
//        }
//        int stay = fn(i1-1, i2, s1, s2, dp);
//        return dp[i1][i2] = move + stay;
//    }

    int subsequenceCounting(string s1, string s2) {
        int len1 = s1.size();
        int len2 = s2.size();

        v2t dp(len1 + 1, vector<int>(len2 + 1, 0));

        for (int i1 = 0; i1 <= len1; ++i1) dp[i1][0] = 1;

        for (int i1 = 1; i1 <= len1; ++i1) {
            for (int i2 = 1; i2 <= len2; ++i2) {
                int move = 0;
                if (s1[i1 - 1] == s2[i2 - 1]) {
                    move = dp[i1 - 1][i2 - 1];
                }
                int stay = dp[i1 - 1][i2];
                dp[i1][i2] = move + stay;
            }
        }
        return dp[len1][len2];
    }
};

class S4 {
public:
//    int fn(int i1, int i2, string &s1, string &s2, v2t &dp){
//        if(i2 < 0) return 1;
//        if(i1 < 0) return 0;
//        if(dp[i1][i2] != -1) return dp[i1][i2];
//
//        int move = 0;
//        if(s1[i1] == s2[i2]){
//            move = fn(i1-1, i2-1, s1, s2, dp);
//        }
//        int stay = fn(i1-1, i2, s1, s2, dp);
//        return dp[i1][i2] = move + stay;
//    }

    int subsequenceCounting(string s1, string s2) {
        int len1 = s1.size();
        int len2 = s2.size();

//        v2t dp(len1+1, vector<int>(len2+1, 0));
        vector<int> dp(len2 + 1, 0);

//        for(int i1 = 0; i1 <= len1; ++i1) dp[i1][0] = 1;
//        for(int i1 = 0; i1 <= len1; ++i1) dp[i1][0] = 1;

        for (int i1 = 1; i1 <= len1; ++i1) {
            dp[0] = 1;
            for (int i2 = len2; i2 >= 1; --i2) {
                int move = 0;
                if (s1[i1 - 1] == s2[i2 - 1]) {
                    move = dp[i2 - 1];
                }
                int stay = dp[i2];
                dp[i2] = move + stay;
            }
        }
        return dp[len2];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Count subsequences producing given string", "[tag1]", Solution, S2, S3, S4) {
//@formatter:off
    auto [msg, s1, s2, expected] = GENERATE(table<string, string, string, int>({
        { "T1 ", "babgbag", "bag", 5 },
        { "T2 ", "aaa", "aa", 3 },
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.subsequenceCounting(s1, s2) == expected);
    }
}
