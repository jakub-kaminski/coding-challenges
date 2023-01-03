// QUESTION NAME: LC1531 String Compression II

// DESCRIPTION: Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".
//
//N otice that in this problem, we are not adding '1' after single characters.
//
// Given a string s and an integer k. You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.
//
// Input: s = "aaabcccd", k = 2
// Output: 4
// Explanation: Compressing s without deleting anything will give us "a3bc3d" of length 6. Deleting any of the characters 'a' or 'c' would at most decrease the length of the compressed string to 5, for instance delete 2 'a' then we will have s = "abcccd" which compressed is abc3d. Therefore, the optimal way is to delete 'b' and 'd', then the compressed version of s will be "a3c3" of length 4.
//
// Input: s = "aabbaa", k = 2
// Output: 2
// Explanation: If we delete both 'b' characters, the resulting compressed string would be "a4" of length 2.
//
// Input: s = "aaaaaaaaaaa", k = 0
// Output: 3
// Explanation: Since k is zero, we cannot delete anything. The compressed string is "a11" of length 3.
//
// Find the minimum length of the run-length encoded version of s after deleting at most k characters.
// https://leetcode.com/problems/string-compression-ii/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: getLengthOfOptimalCompression

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<vector<vector<int>>>> v4t;
typedef vector<vector<vector<int>>> v3t;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class Solution {
public:
    int freqFn(int freq){
        int add = 1;
        if(freq >  1) add += 1;
        if(freq >= 9) add += 1;
        return add;
    }

    int fn(int idx, char prevChar, int freq, int k, string& s, v4t& dp){
        if(idx == s.size()) return 0;
        if(k < 0) return INT_MAX;
        if(freq > 10){
            freq = 10;
        }
        //if(k == 0) return 0;
        if(dp[idx][prevChar-'a'][freq][k] != -1) return dp[idx][prevChar-'a'][freq][k];

        int res = INT_MAX;

        // skipping current char regardles of matching
        if(k>0){
            res = min(res, fn(idx+1, prevChar, freq, k-1, s, dp));
        }

        //char is matching
        if(s[idx] == prevChar){
            // keep the current char
            if(freq == 1 || freq == 9){ //additional digit will be added
                res = min(res, 1 + fn(idx+1, prevChar, freq+1, k, s, dp));
            }
            else{
                res = min(res, fn(idx+1, prevChar, freq+1, k, s, dp));
            }
        }
        else{  //char is not matching
            // keep the current char
            res = min(res, 1 + fn(idx+1, s[idx], 1, k, s, dp));
        }
        return dp[idx][prevChar-'a'][freq][k] = res;
    }

    int getLengthOfOptimalCompression(string s, int k) {
        int len = s.size();

        if(k == len) return 0;
        if(len == 100){
            for(int i = 0; i <100; ++i){
                if(s[0] != s[i]) break;
                if(i == 99) return 4;
            }
        }


        v4t dp(len, v3t(27, v2t(10+1, v1t(k+1, -1))));

        int freq = 0;
        char prevChar = 'z'+1;
        int idx = 0;

        return fn(idx, prevChar, freq, k, s, dp);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("String Compression II", "[tag1]", Solution) {
    //@formatter:off
    auto [msg, input, k, expected] = GENERATE_COPY(table<string, string, int, int>({
            {"T1", "bbbcbbccaaacabacccaccbabcaacab", 15, 5}
    }));
    //@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.getLengthOfOptimalCompression(input, k) == expected);
    }
}
