// QUESTION NAME: LC0132 Palindrome Partitioning

// DESCRIPTION: Given a string s, partition s such that every substring of the partition is a palindrome. Return the minimum cuts needed for a palindrome partitioning of s.
//
// Input: s = "aab"
// Output: 1
// Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

// Input: s = "a"
// Output: 0
//
// Input: s = "ab"
// Output: 1
// https://leetcode.com/problems/palindrome-partitioning-ii/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: minCut

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

struct Solution1 {
    bool isPalindrome(int i, int j, string &s){
        while(i < j){
            if( s[i] != s[j]) return false;
            ++i;
            --j;
        }
        return true;
    }

    int fn(int i, string& s, vector<int> &dp){
        if(i == s.size()) return 0;
        if(dp[i] != -1) return dp[i];

        int numPalindromes = INT_MAX;

       for(int j = i; j < s.size(); ++j){
           if(isPalindrome(i,j,s)){
               numPalindromes = min(numPalindromes, 1 + fn(j+1, s, dp));
           }
       }
       return dp[i] = numPalindromes;
    }
    int minCut(string s) {
        vector<int> dp(s.size(), -1);
        return fn(0, s, dp) - 1;
    }
};

struct Solution2 {
    bool isPalindrome(int i, int j, string &s){
        while(i < j){
            if( s[i] != s[j]) return false;
            ++i;
            --j;
        }
        return true;
    }

    int minCut(string s) {
        vector<int> dp(s.size()+1, 0);

        for(int i = s.size()-1; i >= 0; --i){
            int numPalindromes = INT_MAX;

            for(int j = i; j < s.size(); ++j){
                if(isPalindrome(i,j,s)){
                    numPalindromes = min(numPalindromes, 1 + dp[j+1]);
                }
            }
            dp[i] = numPalindromes;
        }
        return dp[0] - 1;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Stair Climbing DP", "[tag1]", Solution1, Solution2) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, string, int>({
            {"T1",  "aab", 1},
            {"T2",  "a", 0},
            {"T3",  "ab", 1},
            {"T4",  "acbebcaxyx", 1},
            {"T5", "ala", 0},
            {"T6", "abcd", 3},
            {"T7", "abbacd", 2},
            {"T8", "abbaca", 2}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.minCut(input) == expected);
    }
}
