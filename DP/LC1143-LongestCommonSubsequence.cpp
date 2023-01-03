// QUESTION NAME: LC01143 Longest Increasing Subsequence

// DESCRIPTION: Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
//
//A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
//For example, "ace" is a subsequence of "abcde".
//A common subsequence of two strings is a subsequence that is common to both strings.
//
//Input: text1 = "abcde", text2 = "ace"
//Output: 3
//Explanation: The longest common subsequence is "ace" and its length is 3.
//
// Input: text1 = "abc", text2 = "abc"
// Output: 3
// Explanation: The longest common subsequence is "abc" and its length is 3.
//
// Input: text1 = "abc", text2 = "def"
// Output: 0
// Explanation: There is no such common subsequence, so the result is 0.

// APPROACH:
// Recursion, DP

// FUNCTION NAME: longestCommonSubsequence


#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;

struct S1 {
    int fn(int a, int b, string &s1, string &s2) {
        if (a < 0 || b < 0) return 0;
        if (s1[a] == s2[b]) return 1 + fn(a - 1, b - 1, s1, s2);

        int move_a = fn(a - 1, b, s1, s2);
        int move_b = fn(a, b - 1, s1, s2);
        return max(move_a, move_b);
    }

    int longestCommonSubsequence(string s1, string s2) {
        int len1 = s1.size();
        int len2 = s2.size();

        return fn(len1 - 1, len2 - 1, s1, s2);
    }
};

struct S2 {
    int fn(int a, int b, string &s1, string &s2, v2t &dp) {
        if (a < 0 || b < 0) return 0;
        if (dp[a][b] != -1) return dp[a][b];
        if (s1[a] == s2[b]) return 1 + fn(a - 1, b - 1, s1, s2, dp);

        int move_a = fn(a - 1, b, s1, s2, dp);
        int move_b = fn(a, b - 1, s1, s2, dp);
        return dp[a][b] = max(move_a, move_b);
    }

    int longestCommonSubsequence(string s1, string s2) {
        int len1 = s1.size();
        int len2 = s2.size();

        v2t dp(len1, vector<int>(len2, -1));
        return fn(len1 - 1, len2 - 1, s1, s2, dp);
    }
};

struct S3 {
    //  a b x c
    //b - 1 - -
    //a 1 - - -
    //c - - - 1

    int longestCommonSubsequence(string s1, string s2) {
        int len1 = s1.size();
        int len2 = s2.size();

        v2t dp(len1 + 1, vector<int>(len2 + 1, 0));
//        for(int i = 0; i <= len1; ++i){
//            if(s1[i] == s2[0]) dp[i][0] = 0;
//        }
//        for(int j = 0; j <= len2; ++j){
//            if(s1[0] == s2[j]) dp[0][j] = 0;
//        }

        for (int a = 1; a <= len1; ++a) {
            for (int b = 1; b <= len2; ++b) {
                if (s1[a - 1] == s2[b - 1]) {
                    dp[a][b] = 1 + dp[a - 1][b - 1];
                    continue;
                }
                int move_a = dp[a - 1][b];
                int move_b = dp[a][b - 1];
                dp[a][b] = max(move_a, move_b);
//                if(a==1 && b ==1 && dp[0][0] == 1) dp[a][b] = 1;
            }
        }
        return dp[len1][len2];
//        return dp[len1- 1][len2 - 1];
//        int maxi = INT_MIN;
//        for (int k = 0; k < len2; k++){
//            maxi = max(maxi, dp[len1-1][k]);
//        }
//        for (int k = 0; k < len1; k++){
//            maxi = max(maxi, dp[k][len2-1]);
//        }
//        return maxi;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Longest Matching substrings", "", S1, S2, S3) {

////@formatter:off
    auto [msg, s1, s2, expected] = GENERATE(table<string, string, string, int>({
    {
    "T1: 8 letters",
    "axbxxcxx",
    "yayyyybc",
    3
    },
    {
    "T2: 8 letters, single letter matching in order",
    "xxxxxabc",
    "cbayyyyy",
    1
    },
    {
    "T3: 8 letters, two letters matching in order",
    "xxxxxabc",
    "yyyyyyab",
    2
    },
    {
    "T4: 8 letters, two letters matching in order",
    "abxcxabcxx",
    "caybyyabyy",
    4
    },
    {
            "T5: 4 letters, duplicates",
            "abab",
            "ab",
            2
    },
    {
            "T6: 5 letters, duplicates",
            "xabcba",
            "yabcbcba",
            5
    },
    }));
////@formatter:on

    TestType solver;
    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.longestCommonSubsequence(s1, s2) == expected);
    }
}
