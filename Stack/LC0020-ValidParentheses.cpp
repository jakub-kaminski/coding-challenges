/// QUESTION NAME: LC0020 Valid Parentheses

// DESCRIPTION:
// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
// determine if the input string is valid.
//
// An input string is valid if:
//
// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.
// Every close bracket has a corresponding open bracket of the same type.

// APPROACH:
//

// FUNCTION NAME: isValid


#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        string startSeq = "[{(";
        string endSeq = "]})";
        for(char c : s){
            if(startSeq.find(c) != string::npos){
                st.push(c);
            }
            else{
                if(!st.empty() && endSeq.find(c) == startSeq.find(st.top())){
                    st.pop();
                }
                else return false;
            }
        }
        return st.empty();
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Valid Parentheses", "[tag1]", Solution) {
//@formatter:off
auto [msg, input, expected] = GENERATE_COPY(table<string, string, bool>({
    {"T1", "{{([])}}", true},
    {"T2", "{{([)]}}", false},
    {"T3", "{{([)}}", false},
    {"T4", "{([])}}", false},
    {"T5", "{({[])}}", false},
    {"T6", "({}{}[])", true},
    {"T7", "]", false},
}));
//@formatter:on
TestType solver;

SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.isValid(input);
        CAPTURE(result);
        CHECK(result == expected);
}
}
