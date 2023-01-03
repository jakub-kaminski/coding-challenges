// QUESTION NAME: SDP0034 Wildcard Matching

// DESCRIPTION: check if wildcard string s1 matches string s2.
// https://www.codingninjas.com/codestudio/problems/wildcard-pattern-matching_701650

// APPROACH:
// Recursion, DP

// FUNCTION NAME: wildcardMatching

#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;

class Solution {
public:
    bool fn(int i, int j, string &s1, string &s2){
        if(i == -1 && j == -1) return true;
        if(i == -1 || j == -1) return false;

        if(s1[i] == s2[j] || s1[i] == '?') return fn(i-1,j-1,s1,s2);
        if(s1[i] == '*'){
            for(int k = j; k >= 0; --k){
                if(fn(i-1, k, s1, s2)) return true;
            }
        }
        return false;
    }
    bool wildcardMatching(string s1, string s2){
        int len1 = s1.size();
        int len2 = s2.size();

        return fn(len1-1, len2 -1, s1, s2);
    }
};


struct S2 {
    bool fn(int i, int j, string &s1, string &s2, v2t &dp){
        if(i == -1 && j == -1) return true;
        if(j == -1 && i >= 0){
            for(int k = i; k >= 0; --k)
                if(s1[k] != '*') return false;
            return true;
        }
        if(i == -1 || j == -1) return false;
        if(dp[i][j] != -1) return bool(dp[i][j]);

        if(s1[i] == s2[j] || s1[i] == '?') return dp[i][j] = fn(i-1,j-1,s1,s2, dp);
        if(s1[i] == '*'){
            return dp[i][j] = fn(i-1, j, s1, s2, dp) || fn(i, j-1, s1, s2, dp);
//            for(int k = j; k >= 0; --k){
//                if(fn(i-1, k, s1, s2, dp) || fn(i, k, s1, s2, dp)) return dp[i][j] = true;
//            }
        }
        return dp[i][j] = false;
    }
    bool wildcardMatching(string s1, string s2){
        int len1 = s1.size();
        int len2 = s2.size();
        v2t dp(len1, vector<int>(len2, -1));
        return fn(len1-1, len2 -1, s1, s2, dp);
    }
};

struct S3 {
    bool wildcardMatching(string s1, string s2){
        int len1 = s1.size();
        int len2 = s2.size();
        v2t dp(len1+1, vector<int>(len2+1, 0));

        dp[0][0] = true;

        for(int i = 1; i <= len1; ++i){
            for(int j = 1; j <= len2; ++j){
                if(s1[i-1] == s2[j-1] || s1[i-1] == '?') dp[i][j] = dp[i-1][j-1];
                if(s1[i-1] == '*'){
                    for(int k = j; k >= 0; --k){
                        if(dp[i-1][k]){ dp[i][j] = true; break; }
                        dp[i][j] = false;
                    }
                }
            }
        }
        return dp[len1][len2];
    }
};

struct S4 {
    bool wildcardMatching(string s1, string s2){
        int len1 = s1.size();
        int len2 = s2.size();
//        v2t dp(len1+1, vector<int>(len2+1, 0));
        vector<int> prev(len2+1, 0);

        prev[0] = true;

        for(int i = 1; i <= len1; ++i){
            vector<int> curr(len2+1, 0);
            for(int j = 1; j <= len2; ++j){
                if(s1[i-1] == s2[j-1] || s1[i-1] == '?') curr[j] = prev[j-1];
                else if(s1[i-1] == '*'){
                    for(int k = j; k >= 0; --k){
                        if(prev[k]){ curr[j] = true; break; }
                        curr[j] = false;
                    }
                }
            }
            prev = curr;
        }
        return prev[len2];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Wildcard matching", "[tag1]", Solution, S2, S3, S4) {
//@formatter:off
    auto [msg, s1, s2, expected] = GENERATE(table<string, string, string, bool>({
        { "T1", "car?", "cars", true },
        { "T2", "c?r", "car", true },
        { "T3", "c*r", "crater", true },
        { "T4", "c*", "parrot", false },
        { "T5", "car*", "carrot", true },
        { "T6", "aa", "a", false },
        { "T7", "*", "aa", true },
        { "T8", "?a", "cb", false },
        { "T9", "*a*b.txt", "adceb", true },
        { "T10", "a*c?b.txt", "acdcb", false },
        { "T11", "b.txt?**?", "ababaa", false }
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.wildcardMatching(s1, s2) == expected);
    }
}
