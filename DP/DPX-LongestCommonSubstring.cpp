// QUESTION NAME: DPX-LongestCommonSubstring

// DESCRIPTION: given two strings choose their letters (in ordered fashion) such that a longest common substing is solved. Return any string if several solutions exist.

// APPROACH:
// Recursion, DP

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;

struct S1 {
    string solve(string s1, string s2) {
        int len1 = s1.size();
        int len2 = s2.size();
        v2t dp(len1+1, vector<int>(len2+1, 0));
        int i_max = 0;
        int j_max = 0;
        int len_max = 0;

        for(int i = 1; i <=len1; ++i){
            for(int j = 1; j <=len2; ++j){
                if(s1[i] == s2[j]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                    if(dp[i][j] > dp[i_max][j_max]){
                        i_max = i;
                        j_max = j;
                        len_max = dp[i][j];
                    }
                }
            }
        }

        string result ="";
        for(int a = i_max - (len_max -1); a <=i_max; ++a){
            result += s1[a];
        }

        return result;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Longest common substring", "", S1) {

////@formatter:off
    auto [msg, s1, s2, expected] = GENERATE(table<string, string, string, vector<string>>({
    {
    "T1: 8 letters",
    "axbcxcxx",
    "yayyyybc",
    {"bc"},
    },
    {
    "T2: 8 letters, single letter matching in order",
    "xxxxxabc",
    "cbayyyyy",
    {"c", "b", "a"},
    },
    {
    "T3: 8 letters, two letters matching in order",
    "xxxxxabc",
    "yyyyyyab",
    {"ab"},
    },
    {
    "T4: 8 letters, two letters matching in order",
    "abxcxabycxx",
    "caybyyabxyyc",
    {"ab","yc", "by", "bx"},
    }
    }));
////@formatter:on

    TestType solver;
    SECTION(msg) {
        CAPTURE(msg);
        string res = solver.solve(s1, s2);
        CAPTURE(res);
        bool success = false;
        for(auto &it : expected)
            if(it == res) success = true;
        CHECK(success == true);
    }
}
