/// QUESTION NAME: LC0125 ValidPalindrome

// DESCRIPTION:
// A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
// and removing all non-alphanumeric characters, it reads the same forward and backward.
// Alphanumeric characters include letters and numbers.
// Given a string s, return true if it is a palindrome, or false otherwise.
//
// Input: s = "A man, a plan, a canal: Panama"
// Output: true
// Explanation: "amanaplanacanalpanama" is a palindrome.
//
// Input: s = "race a car"
// Output: false
// Explanation: "raceacar" is not a palindrome.
//
// Input: s = " "
// Output: true
// Explanation: s is an empty string "" after removing non-alphanumeric characters.
// Since an empty string reads the same forward and backward, it is a palindrome.

// APPROACH:
//

// FUNCTION NAME: isPalindrome

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;


class Solution {
private:
    char lo(char c){
        if(c <= 'Z') return char(c + 32);
        return c;
    }

public:
    bool isPalindrome(string s) {
        int l = 0;
        int r = s.size()-1;

        string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

        while(l<r){
            if(valid.find(s[l]) == string::npos){++l; continue;}
            if(valid.find(s[r]) == string::npos){--r; continue;}

            //cout << "1: "<< lo(s[l]) <<endl;
            //cout << "2: "<< lo(s[r]) <<endl;

            if(lo(s[l]) != lo(s[r])) return false;
            ++l;
            --r;
        }
        return true;
    }
};

TEMPLATE_TEST_CASE("Valid Palindrome", "[tag1]", Solution) {
//@formatter:off
auto [msg, str, expected] = GENERATE_COPY(table<string, string, bool>({
    {"T1:", "A man, a plan, a canal: Panama", true},
    {"T2:", "race a car", false},
    {"T3:", " ", true},
    {"T4:", "0P", false},
    {"T5:", "0P0", true},
}));
//@formatter:on
TestType solver;

SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.isPalindrome(str);
        CAPTURE(result);
        CHECK(result == expected);
}
}
