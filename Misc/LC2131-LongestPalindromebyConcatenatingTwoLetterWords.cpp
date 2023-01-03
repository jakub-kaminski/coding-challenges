// QUESTION NAME: LC0070 Climbing Stairs

// DESCRIPTION: Count the number of unique ways to climb stairs
// You are given an array of strings words. Each element of words consists of two lowercase English letters.
//
// Create the longest possible palindrome by selecting some elements from words
// and concatenating them in any order. Each element can be selected at most once.
//
// Return the length of the longest palindrome that you can create.
// If it is impossible to create any palindrome, return 0.
//
// A palindrome is a string that reads the same forward and backward.
//
// https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/
//
// Input: words = ["lc","cl","gg"]
// Output: 6
// Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
// Note that "clgglc" is another longest palindrome that can be created.
//
// Input: words = ["ab","ty","yt","lc","cl","ab"]
// Output: 8
// Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
// Note that "lcyttycl" is another longest palindrome that can be created.
//
// Input: words = ["cc","ll","xx"]
// Output: 2
// Explanation: One longest palindrome is "cc", of length 2.
// Note that "ll" is another longest palindrome that can be created, and so is "xx".
//
// 1 <= words.length <= 10^5
// words[i].length == 2
// words[i] consists of lowercase English letters.

// APPROACH:
// Hashmaps

// FUNCTION NAME: longestPalindrome

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
array<int,2> enc(string s){
    array<int,2> res = {s[0]-'a', s[1] - 'a'};
    return res;
}
public:
    int longestPalindrome(vector<string>& words) {
        map<array<int,2>,pair<int,int>> diverse;
        map<array<int,2>, int> equal;

        for(string w : words){
            array<int,2> wnum = enc(w);
            if(wnum[0] == wnum[1]){
                equal[wnum]++;
            }
            // two different letters
            else{
               if(wnum[0] < wnum[1]){
                    diverse[wnum].first += 1;
               }
                else{
                    array<int,2> swapped = {wnum[1], wnum[0]};
                    diverse[swapped].second += 1;
                }
            }
        }

        int sumGroups = 0;
        int centerOne = 0;
        for(auto el : diverse){
            sumGroups += 2 * min(el.second.first, el.second.second);
        }

        for(auto el : equal){
            sumGroups += 2 * (el.second / 2);
            centerOne = centerOne || el.second % 2;
        }

        return 2 * (sumGroups + centerOne);
    }
};

// dd = 1 /2 =
// aa  = 3
// bb  = 2
// cc  = 5 /2 * 2 = 4

// diverse1 ... diverse2  equal2 equal1 equal2 diverse_inv2 diverse_inv1

// IMPLEMENTATION ENDS


TEMPLATE_TEST_CASE("Stair Climbing DP", "[tag1]", Solution) {
//TEMPLATE_TEST_CASE("Climbing Stairs", "[tag1]", TabulationMemoSolution, RecursiveMemoSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<string>, int>({
           {"T1",  {"lc","cl","gg"}, 6},
           {"T2",  {"ab","ty","yt","lc","cl","ab"}, 8},
           {"T3",  {"cc","ll","xx"}, 2},
           {"T3",  {"cx"}, 0},
           {"T4",  {}, 0},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.longestPalindrome(input) == expected);
    }
}
