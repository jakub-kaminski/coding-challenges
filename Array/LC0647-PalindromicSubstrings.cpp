// QUESTION NAME: LC0647 Palindromic Substrings

// DESCRIPTION:
// Given a string s, return the number of palindromic substrings in it.
// A string is a palindrome when it reads the same backward as forward.
// A substring is a contiguous sequence of characters within the string.
//
// Input: s = "abc"
// Output: 3
// Explanation: Three palindromic strings: "a", "b", "c".
//
// Input: s = "aaa"
// Output: 6
// Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
//
// 1 <= s.length <= 1000
// s consists of lowercase English letters.

// APPROACH:
//

// FUNCTION NAME: longestPalindrome

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int countSubstrings(string s) {
        int len = s.size();

        int res = len;
        for (int i = 1; i < len; ++i) {
            if (s[i] == s[i - 1]) {
                int l = i - 1;
                int r = i;
                while (l >= 0 && r < len && s[l] == s[r]) {
                    ++res;
                    --l;
                    ++r;
                }
            }
            if (i > 0 && i < len - 1 && s[i - 1] == s[i + 1]) {
                int l = i - 1;
                int r = i + 1;
                while (l >= 0 && r < len && s[l] == s[r]) {
                    ++res;
                    --l;
                    ++r;
                }
            }
        }

        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Number of non-unique palindromic substrings", "[tag1]", Solution) {
//@formatter:off
    auto [msg, s, expected] = GENERATE(table<string, string, int>({
        {"T1", "babad", 7}, // bab aba b a b a d
        {"T2", "ac", 2}, // a c
        {"T3", "abbbc", 8}, // bb bb bbb a b b b c
        {"T4", "aaa", 6}, // aa aa aaa a a a
        {"T5", "a", 1}, // a
        {"T6", "aa", 3}, // aa  a a
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.countSubstrings(s);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
