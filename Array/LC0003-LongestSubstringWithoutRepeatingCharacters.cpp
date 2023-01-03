// QUESTION NAME: LC0003 Longest Substring Without Repeating Characters

// DESCRIPTION: Given a string s, find the length of the longest substring without repeating characters.
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
//
// Input: s = "abcabcbb"
// Output: 3
// Explanation: The answer is "abc", with the length of 3.
//
// Input: s = "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
//
// Input: s = "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3.
// Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
//
//0 <= s.length <= 5 * 10^4
//s consists of English letters, digits, symbols and spaces

// APPROACH:
//

// FUNCTION NAME: lengthOfLongestSubstring

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

typedef int out_type;
typedef std::string in_type;
using std::string;
using std::set;

class Solution {
public:
    int lengthOfLongestSubstring(string &s) {
        std::unordered_map<char, int> map;
        int len = s.size();
        int max_len = 0;
        int len_now = 0;
        int left = -1;

        for (int i = 0; i < len; ++i) {
            if (map.count(char(s[i]))) {
                if (map[char(s[i])] > left)
                    left = map[char(s[i])];
            }
            len_now = i - left;
            max_len = std::max(max_len, len_now);
            map[char(s[i])] = i;
        }
        return max_len;
    }
};


// NOT FULLY-FUNCTIONAL
//struct OptSolutionSet {
//    out_type lengthOfLongestSubstring(in_type &s) {
//        std::unordered_set<char> set;
//        int len = s.size();
//        int left = -1;
//        int res = 0;
//
//        for (int i = 0; i < len; ++i) {
//            while(set.contains(char(s[i]))) {
//                set.erase(char(s[i]));
//                left++;
//            }
//           set.insert(char(s[i]));
//            res = std::max(res, i - left);
//        }
//        return res;
//    }
//};

// Credits: https://leetcode.com/problems/longest-substring-without-repeating-characters/discuss/577010/C%2B%2B-Solution-using-Set
// Cool explanation how left pointer removes stuff from set:  https://leetcode.com/problems/longest-substring-without-repeating-characters/discuss/577010/C++-Solution-using-Set/1419961
struct OptSolutionSet2 {
    out_type lengthOfLongestSubstring(in_type &s) {
        int len = s.length();
        if (len == 0)
            return 0;
        set<char> st;
        int maxsize = 0;
        int i = 0, j = 0;
        while (j < len) {
            if (st.count(s[j]) == 0) {
                st.insert(s[j]);
                maxsize = std::max(maxsize, (int) st.size());
                j++;
            } else {
                st.erase(s[i]);
                i++;
            }
        }
        return maxsize;
    }
};

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("Longest Substring Without Repeating Characters", "[tag1]", OptSolution, OptSolutionSet, OptSolutionSet2) {
TEMPLATE_TEST_CASE("Longest Substring Without Repeating Characters", "[tag1]", Solution, OptSolutionSet2) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type, out_type>({
            {"single repeated letter:", "aaaaa", 1},
            {"sequences of 3 letters", "abcabcabc", 3},
            {"sequence of returning letters", "abba", 2},
            {"two distinct letters", "au", 2},
            {"repeated and single letter", "aau", 2},
            {"repeated 2 times and on last place", "pwwkew", 3}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.lengthOfLongestSubstring(input) == expected);
    }
}