// QUESTION NAME: LC0424 Longest Repeating Character Replacement

// DESCRIPTION:
// You are given a string s and an integer k.
// You can choose any character of the string and change it
// to any other uppercase English character.
// You can perform this operation at most k times.
//
// Return the length of the longest substring containing
// the same letter you can get after performing the above operations.
//
// Input: s = "ABAB", k = 2
// Output: 4
// Explanation: Replace the two 'A's with two 'B's or vice versa.
//
// Input: s = "AABABBA", k = 1
// Output: 4
// Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
// The substring "BBBB" has the longest repeating letters, which is 4.
//
// 1 <= s.length <= 10^5
// s consists of only uppercase English letters.
// 0 <= k <= s.length
//
// https://leetcode.com/problems/longest-repeating-character-replacement/

// APPROACH:
//

// FUNCTION NAME: characterReplacement

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        int len = s.size();
        vector<int> m(26,0);

        int maxFreq = 0;
        int maxLen =0;
        int l = 0;
        for(int r = 0; r < len; ++r){
            m[s[r]-'A'] += 1;

            if(m[s[r]-'A'] > maxFreq){
                maxFreq = m[s[r]-'A'];
            }
            while(accumulate(m.begin(), m.end(), 0) - maxFreq > k){
                m[s[l] - 'A'] -= 1;
                maxFreq = *max_element(m.begin(), m.end());
                if(l < len-1) ++l;
            }
            maxLen = max(maxLen, r-l + 1);
        }
        return maxLen;
    }
};


class Solution2 {
public:
  int characterReplacement(string s, int k) {
      int len = s.size();
      if(k >= len-1) return len;

      vector<int> alp(26, 0);

      ++k;

      int taken = 0;

      int i=0;
      int l = 0;
      int maxLen = 0;

      while(i < len){
        while(i <len && (taken < k || alp[int(s[i]-'A')] != 0)){
          if(alp[int(s[i]-'A')] == 0) taken++;
          alp[int(s[i]-'A')] += 1;
          ++i;
          maxLen = max(maxLen, i-l);
        }
        while(taken >= k){
          alp[int(s[l]-'A')] -= 1;
          if(alp[int(s[l]-'A')] == 0) --taken;
          ++l;
        }
      }
      return maxLen;
  }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Three Sum", "[tag1]", Solution) {
//@formatter:off
auto [msg, input, k, expected] = GENERATE(table<string, string, int, int>({
{"T1", "AABABBA", 1, 4},
{"T2", "ABAB", 2, 4},
}));
//@formatter:on
TestType solver;

SECTION(msg) {
        CAPTURE(msg);

        auto result = solver.characterReplacement(input, k);

        CAPTURE(result);
        CHECK(result == expected);
}
}
