// QUESTION NAME: LC0012 Integer To Roman

// DESCRIPTION: Given an integer, convert it to a roman numeral.
//
// https://leetcode.com/problems/integer-to-roman/

// APPROACH:
// Create artificial two-letters strings in between of the roman letters
// Create a matching values array and iterated over it substracting from input number
//
// 3 % 5 = 3
// 3 / 5 = 0
//
// 4 % 5 = 4
// 4 / 5 = 0
// IV
//
// 30 % 50 = 30
// 30 / 50 = 0
//
// 40 % 50 = 40
// 40 / 50 = 0
// XL

// FUNCTION NAME: intToRoman

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        vector<string> symbols{"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
        vector<int> vals{1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
        string res = "";
        int i = vals.size()-1;
        while(num != 0){
            if(num/vals[i] > 0){
                for(int j = 0; j < num/vals[i]; ++j){
                    res += symbols[i];
                }
                num -= vals[i] * (num/vals[i]);
            }
            else{
                --i;
            }
        }
        return res;
    }
};

class Solution3 {
public:
    string intToRoman(int num) {
        vector<string> symbols{"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
        vector<int> vals{1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
        string res = "";
        int i = vals.size()-1;
        while(num != 0){
            if(num >= vals[i]){
                num -= vals[i];
                res += symbols[i];
            }
            else{
                --i;
            }
        }
        return res;
    }
};

class Solution2 {
public:
    string intToRoman(int num) {

        string thousands_res = "";
        int solid_thousands = num / 1000;
        for (int i = 0; i < solid_thousands; ++i) {
            thousands_res += "M";
        }

        vector<string> symbols = {"I", "V", "X", "L", "C", "D", "M"};
        int len = symbols.size();

        string res = "";
        for (int i = 0; i < len - 2; i += 2) {
            if (num == 0) break;
            string str_now = "";
            if (num % 5 == 4) {
                if ((num / 5) % 2 == 1) {
                    // IX
                    str_now = symbols[i] + symbols[i + 2];
                } else if ((num / 5) % 2 == 0) {
                    //IV
                    str_now = symbols[i] + symbols[i + 1];
                }
            }
            else {
                // Optional V
                if ((num / 5) % 2 == 1) {
                    //V
                    str_now = symbols[i + 1];
                }

                //I, II, III
                for (int k = 0; k < num % 5; ++k) {
                    str_now += symbols[i];
                }
            }
            num /= 10;
            res.insert(0, str_now);
        }
        if(solid_thousands > 0){
        res.insert(0, thousands_res);
        }
        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Integer to Roman", "[tag1]", Solution, Solution2) {
//TEMPLATE_TEST_CASE("4 Sum, Return unique quadruplets", "[tag1]", LeetcodeSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, int, string>({
        {"T01: ", 1, "I"},
        {"T02: ", 3, "III"},
        {"T03: ", 4, "IV"},
        {"T04: ", 6, "VI"},
        {"T05: ", 8, "VIII"},
        {"T06: ", 9, "IX"},
        {"T07: ", 10, "X"},
        {"T08: ", 11, "XI"},
        {"T09: ", 14, "XIV"},
        {"T10: ", 19, "XIX"},
        {"T11: ", 49, "XLIX"},
        {"T12: ", 101, "CI"},
        {"T13: ", 134, "CXXXIV"},
        {"T14: ", 149, "CXLIX"},
        {"T15: ", 3949, "MMMCMXLIX"},
        {"T16: ", 3999, "MMMCMXCIX"},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.intToRoman(input);
        CAPTURE(result);
        CHECK(result == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.fourSum(input); };

}
