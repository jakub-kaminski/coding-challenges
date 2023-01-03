// question name: LC1239 Maximum Length of a Concatenated String with Unique Characters

// DESCRIPTION:
// You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.
//
// Return the maximum possible length of s.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Input: arr = ["un","iq","ue"]
// Output: 4
// Explanation: All the valid concatenations are:
// - ""
// - "un"
// - "iq"
// - "ue"
// - "uniq" ("un" + "iq")
// - "ique" ("iq" + "ue")
// Maximum length is 4.
//
// Input: arr = ["cha","r","act","ers"]
// Output: 6
// Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").
//
// Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
// Output: 26
// Explanation: The only string in arr has all 26 characters.

// https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/

// APPROACH:
//

// FUNCTION NAME: maxLength

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class Solution {
public:
    int fn(int i, vector<int> taken, vector<string>& arr){
        if(i == arr.size()) return 0;
        int noTake = 0 + fn(i+1, taken, arr);

        for(char c : arr[i]){
            if(taken[c-'a'])
                return max(0,noTake);
            else
                ++taken[c-'a'];
        }
        int take = arr[i].size() + fn(i+1, taken, arr);
        return max(take,noTake);
    }

    int maxLength(vector<string>& arr) {
        vector<int> taken(26,0);
        return fn(0, taken, arr);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("DFS", "[tag1]", Solution) {
//@formatter:off
    auto [msg, adjMatrix, expected] = GENERATE(table<string, vector<string>, int>({
        {"T1", {"un","iq","ue"}, 4},
        {"T2", {"cha","r","act","ers"}, 6},
        {"T3", {"abcdefghijklmnopqrstuvwxyz"}, 26},
}));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.maxLength(adjMatrix);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
