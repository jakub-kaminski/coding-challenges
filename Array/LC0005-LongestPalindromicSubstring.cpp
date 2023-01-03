// QUESTION NAME: LC0005 Longest Palindromic Substring

// DESCRIPTION:
// Given a string s, return the longest palindromic substring in s.
//
// Input: s = "babad"
// Output: "bab"
// Explanation: "aba" is also a valid answer.
//
// Input: s = "cbbd"
// Output: "bb"
//
// 1 <= s.length <= 1000
// s consist of only digits and English letters.
//
// https://leetcode.com/problems/longest-palindromic-substring/

// APPROACH:
//

// FUNCTION NAME: longestPalindrome

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        if(len == 1) return s;
        string res = s.substr(0,1);
        for(int i = 1; i < len; ++i){
           if(s[i] == s[i-1]){
               int l = i-1;
               int r = i;
               while(l >= 0 && r < len && s[l] == s[r]){
                  if(r-l+1 > res.size()){
                      res = s.substr(l,r-l+1);
                  }
                  --l;
                  ++r;
               }
           }
           if(i > 0 && i < len-1 && s[i-1] == s[i+1]){
               int l = i-1;
               int r = i+1;
               while(l >= 0 && r < len && s[l] == s[r]){
                  if(r-l+1 > res.size()){
                      res = s.substr(l,r-l+1);
                  }
                  --l;
                  ++r;
               }
           }
        }

        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Longest Palindromic Substring", "[tag1]", Solution) {
//@formatter:off
    auto [msg, s, expected] = GENERATE(table<string, string, string>({
              {"T1", "babad", "bab"},
              {"T2", "ac", "a"},
              {"T3", "abbbc", "bbb"},
      }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.longestPalindrome(s);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
