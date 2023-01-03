// question name: lc0076 minimum window substring

// description:
// input: s = "adobecodebanc", t = "abc"
// output: "banc"
// explanation: the minimum window substring "banc" includes 'a', 'b', and 'c' from string t.
//
// https://leetcode.com/problems/minimum-window-substring/

// approach:
//

// function name: minwindow

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> desired;
        for (char &c: t)
            desired[c]++;

        int conditionsToMeet = t.size();
        unordered_map<char, int> umap;

        int l = 0;
        int r = 0;

        while (r < s.size() && conditionsToMeet > 0) {
//            char cNow = s[r];
//            if(s[r] == 'D'){
//                cout << "hello";
//            }
            if (desired.count(s[r]) > 0) {
                ++umap[s[r]];
                if (umap[s[r]] <= desired[s[r]])
                    --conditionsToMeet;
            }
            if(conditionsToMeet > 0){
                ++r;
            }
        }

        if (conditionsToMeet > 0)
            return "";

        pair<int, int> minFound = {l, r};

        while (l < r && r < s.size()) {

            while (l < r && conditionsToMeet == 0) {
                if (desired.count(s[l])>0) {
                    --umap[s[l]];
                    if (umap[s[l]] < desired[s[l]]) {
                        ++conditionsToMeet;
                    }
                    if (r - l < minFound.second - minFound.first) {
                        minFound = {l, r};
                    }
                }
                ++l;
            }

            while (r < s.size() && conditionsToMeet != 0) {
                if (desired.count(s[r])>0) {
                    ++umap[s[r]];
                    if (umap[s[r]] <= desired[s[r]]) {
                        --conditionsToMeet;
                    }
                }

                if(conditionsToMeet == 0){
                    if (r - l < minFound.second - minFound.first) {
                        minFound = {l, r};
                    }
                }
                ++r;
            }
        }
        string result ="";
        for(int i = minFound.first; i <= minFound.second+1; ++i){
            result += s[i];
        }
        return result;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Number of Islands", "[tag1]", Solution) {
//@formatter:off
    auto [msg, s1, s2, expected] = GENERATE(table<string, string, string, string>({
                                                                                 {"T1", "ADOBECODEBANC", "ABC", "BANC"},
                                                                                 {"T2", "ADOBECODEBANC", "CAB", "BANC"},
                                                                                 {"T3", "ADOBECODEBANCXX", "CAB", "BANC"},
                                                                         }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.minWindow(s1, s2);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
