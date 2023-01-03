/// QUESTION NAME: LC0130 Surrounded Regions

// DESCRIPTION:
// Given an m x n matrix board containing 'X' and 'O',
// capture all regions that are 4-directionally surrounded by 'X'.
// A region is captured by flipping all 'O's into 'X's in that surrounded region.
//
// Input: board = [["X","X","X","X"],
//                 ["X","O","O","X"],
//                 ["X","X","O","X"],
//                 ["X","O","X","X"]]
//
// Output: [["X","X","X","X"],
//          ["X","X","X","X"],
//          ["X","X","X","X"],
//          ["X","O","X","X"]]
//
// Explanation: Notice that an 'O' should not be flipped if:
// - It is on the border, or
// - It is adjacent to an 'O' that should not be flipped.
// The bottom 'O' is on the border, so it is not flipped.
// The other three 'O' form a surrounded region, so they are flipped.

// APPROACH:
//

// FUNCTION NAME: earliestFullBloom

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
    static bool comp(pair<int,int> a, pair<int,int> b){
        return a.second > b.second;
    }
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        int len = plantTime.size();
        vector<pair<int,int>> p;
        p.reserve(len);
        for(int i = 0; i < len; ++i){
            p.push_back({plantTime[i], growTime[i]});
        }

        sort(p.begin(), p.end(), comp);

        int totalTime = 0;
        int totalPlantT = 0;
        for(int k = 0; k < len; ++k){
            totalPlantT += p[k].first;
            totalTime = max(totalTime, totalPlantT + p[k].second);
        }
        return totalTime;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Update 01Matrix", "[tag1]", Solution) {
//@formatter:off
    auto [msg, plantTime, growTime, expected] = GENERATE(table<string, vector<int>, vector<int>, int>({
    {"T1", { 1,4,3 }, {2,3,1}, 9},
    {"T2", { 1,2,3,2 }, { 2,1,2,1 }, 9},
    {"T3", { 3,11,29,4,4,26,26,12,13,10,30,19,27,2,10 }, { 10,13,22,17,18,15,21,11,24,14,18,23,1,30,6 }, 227},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto res = solver.earliestFullBloom(plantTime, growTime);
        CHECK(res == expected);
    }
}
