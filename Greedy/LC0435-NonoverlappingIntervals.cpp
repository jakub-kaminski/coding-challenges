// QUESTION NAME: LC0435 Non-overlapping Intervals

// DESCRIPTION:
// Given an array of intervals intervals where intervals[i] = [starti, endi],
// return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
//
// Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
// Output: 1
// Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.
//
// Input: intervals = [[1,2],[1,2],[1,2]]
// Output: 2
// Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.
//
// Input: intervals = [[1,2],[2,3]]
// Output: 0
// Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
//
// 1 <= intervals.length <= 105
// intervals[i].length == 2
// -5 * 104 <= starti < endi <= 5 * 104
//
// https://leetcode.com/problems/non-overlapping-intervals/

// APPROACH:
// Sort + Greedy

// FUNCTION NAME: eraseOverlapIntervals

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;


bool comp(const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0]) return a[1] < b[1];
    return a[0] < b[0];
}

class Solution {
private:
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals) {

        sort(intervals.begin(), intervals.end(), comp);

        int len = intervals.size();

        int prev = 0;
        int now = 1;
        int res = 0;
        while (now < len) {
            if (intervals[now][0] < intervals[prev][1]) {
                res++;
                if (intervals[now][1] < intervals[prev][1]) {
                    // previous interval exceedes further into positive space
                    // it should be removed. Currently compared now will become the prev we refer to.
                    prev = now;
                    ++now;
                } else {
                    // in other case previous is not updated and only the current interval changes
                    ++now;
                }
            } else {
                // if no overlap, then just increase intervals
                // note that the gap between prev and now can be greater than 1
                prev = now;
                ++now;
            }
        }
        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Non-overlapping intervals", "[tag1]", Solution) {
//TEMPLATE_TEST_CASE("Climbing Stairs", "[tag1]", TabulationMemoSolution, RecursiveMemoSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<vector<int>>, int>({
           {"T1",  {{1,2},{2,3},{3,4},{1,3}}, 1},
           {"T2", {{1,2},{1,2},{1,2}}, 2},
           {"T3", {{1,2},{2,3}}, 0},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.eraseOverlapIntervals(input) == expected);
    }
}
