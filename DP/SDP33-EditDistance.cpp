// QUESTION NAME: DP0033 Edit Distance

// DESCRIPTION: Count the number of operations needed to transform one string to another
// (first string transformed to the second one)
// Allowed operations (each one costs 1):
// - Deletion of a character.
// - Replacement of a character with another one.
// - Insertion of a character.
//
// Example description goes here
// https://www.codingninjas.com/codestudio/problems/edit-distance_630420

// APPROACH:
// Some Approach here

// FUNCTION NAME: editDistance

#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;

class S1 {
private:
    int fn(int i1, int i2, string &s1, string &s2){
        if(i2 < 0) return i1 + 1;
        if(i1 < 0) return i2 + 1;

        if(s1[i1] == s2[i2]) return fn(i1-1,i2-1, s1, s2);

        int addChar = 1 + fn(i1, i2-1, s1, s2);
        int removeChar = 1 + fn(i1-1, i2, s1, s2);
        int replaceChar = 1+ fn(i1-1,i2-1, s1, s2);
        return min({addChar, removeChar, replaceChar});
    }
public:
    int editDistance(string s1, string s2){
        int len1 = s1.size();
        int len2 = s2.size();

        return fn(len1-1, len2-1, s1, s2);
    }
};

class S2 {
    int fn(int i1, int i2, string &s1, string &s2, v2t &dp){
        if(i2 < 0) return i1 + 1;
        if(i1 < 0) return i2 + 1;
        if(dp[i1][i2] != -1) return dp[i1][i2];

        if(s1[i1] == s2[i2]) return dp[i1][i2] = fn(i1-1,i2-1, s1, s2, dp);

        int addChar = 1 + fn(i1, i2-1, s1, s2, dp);
        int removeChar = 1 + fn(i1-1, i2, s1, s2, dp);
        int replaceChar = 1+ fn(i1-1,i2-1, s1, s2, dp);
        return dp[i1][i2] = min({addChar, removeChar, replaceChar});
    }

    int editDistance(string s1, string s2){
        int len1 = s1.size();
        int len2 = s2.size();

        v2t dp(len1, vector<int>(len2,-1));

        return fn(len1-1, len2-1, s1, s2, dp);
    }
};

struct S3 {
    int editDistance(string s1, string s2){
        int len1 = s1.size();
        int len2 = s2.size();

        v2t dp(len1+1, vector<int>(len2+1,0));
        for(int i = 0; i <= len1; ++i) dp[i][0] = i;
        for(int i = 0; i <= len2; ++i) dp[0][i] = i;

        for(int i1 = 1; i1 <= len1; ++i1){
            for(int i2 = 1; i2 <= len2; ++i2){
                if(s1[i1-1] == s2[i2-1]){
                  dp[i1][i2] = dp[i1-1][i2-1];
                  continue;
                }
                int addChar = 1 + dp[i1][i2-1];
                int removeChar = 1 + dp[i1-1][i2];
                int replaceChar = 1 + dp[i1-1][i2-1];
                dp[i1][i2] = min({addChar, removeChar, replaceChar});
            }
        }
        return dp[len1][len2];
    }
};

struct S4 {
    int editDistance(string s1, string s2){
        int len1 = s1.size();
        int len2 = s2.size();

        vector<int> prev(len2+1,0);
        vector<int> curr(len2+1,0);
        for(int i = 0; i <= len2; ++i) prev[i] = i;

        for(int i1 = 1; i1 <= len1; ++i1){
            curr[0] = i1;
            for(int i2 = 1; i2 <= len2; ++i2){
                if(s1[i1-1] == s2[i2-1]){
                    curr[i2] = prev[i2-1];
                    continue;
                }
                int addChar = 1 + curr[i2-1];
                int removeChar = 1 + prev[i2];
                int replaceChar = 1 + prev[i2-1];
                curr[i2] = min({addChar, removeChar, replaceChar});
            }
            prev = curr;
        }
        return prev[len2];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Edit Distance: operations to transform string", "[tag1]", Solution, S2, S3, S4) {
//@formatter:off
    auto [msg, s1, s2, expected] = GENERATE(table<string, string, string, int>({
        { "T1", "horse", "ros", 3 },
        { "T2", "axbc", "ab", 2 },
        { "T3", "ab", "ab", 0 },
        { "T4", "abba", "aba", 1 },
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.editDistance(s1, s2) == expected);
    }
}
