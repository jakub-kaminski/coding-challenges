// QUESTION NAME: LC1047 Remove All Adjacent Duplicates In String

// DESCRIPTION:
// You are given a string s consisting of lowercase English letters.
// A duplicate removal consists of choosing two adjacent and equal letters and removing them.
// We repeatedly make duplicate removals on s until we no longer can.
// Return the final string after all such duplicate removals have been made.
// It can be proven that the answer is unique./
//
// Input: s = "abbaca"
// Output: "ca"
// Explanation:
// For example, in "abbaca" we could remove "bb" since the letters are adjacent and equal,
// and this is the only possible move.  The result of this move is that the string is "aaca",
// of which only "aa" is possible, so the final string is "ca".
//
// Input: s = "azxxzy"
// Output: "ay"
//
// 1 <= s.length <= 105
// s consists of lowercase English letters.

// APPROACH:
// Stack + reverse String

// FUNCTION NAME: removeDuplicates

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {

        stack<char> st;
        st.push(s[0]);

        for (int i = 1; i < s.size(); ++i) {
            if (!st.empty() && st.top() == s[i]) st.pop();
            else st.push(s[i]);
        }

        string res;
        while (!st.empty()) {
            res += st.top();
            st.pop();
        }

        reverse(res.begin(), res.end());
        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Stair Climbing DP", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, string, string>({
           {"One step",  "abbaca", "ca"},
           {"Two steps", "azxxzy", "ay"},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.removeDuplicates(input) == expected);
    }
}
