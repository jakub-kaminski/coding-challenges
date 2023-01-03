// QUESTION NAME: LC0057 Insert Interval

// DESCRIPTION:
// You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi]
// represent the start and the end of the ith interval and intervals is sorted in ascending order by starti.
// You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
//
// Insert newInterval into intervals such that intervals is still sorted in ascending order
// by starti and intervals still does not have any overlapping intervals
// (merge overlapping intervals if necessary).
//
// Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
// Output: [[1,5],[6,9]]
//
// Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
// Output: [[1,2],[3,10],[12,16]]
// Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
//
// 0 <= intervals.length <= 104
// intervals[i].length == 2
// 0 <= starti <= endi <= 105
// intervals is sorted by starti in ascending order.
// newInterval.length == 2
// 0 <= start <= end <= 105
//
// https://leetcode.com/problems/insert-interval/

// APPROACH:
// Sort + Greedy

// FUNCTION NAME: insert

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;


// Credits: Knowledge Center YT Channel, https://www.youtube.com/watch?v=FuLfL_WhUHI
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int i = 0;
        int len = intervals.size();
        //res.reserve(len+1);

        while(i < len && intervals[i][1] < newInterval[0]) res.push_back(intervals[i++]);

        vector<int> middle = newInterval;

        while(i < len && intervals[i][0] <= newInterval[1]){
            middle[0] = min(middle[0], intervals[i][0]);
            middle[1] = max(middle[1], intervals[i][1]);
            ++i;
        }
        res.push_back(middle);

        while(i < len) res.push_back(intervals[i++]);

        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Inset Interval and remove overlaps", "[tag1]", Solution) {
//TEMPLATE_TEST_CASE("Climbing Stairs", "[tag1]", TabulationMemoSolution, RecursiveMemoSolution) {
//@formatter:off
    auto [msg, input, newInterval, expected] = GENERATE(table<string, vector<vector<int>>, vector<int>, vector<vector<int>>>({
       {"T1", {{1,2},{3,5},{6,7},{8,10},{12,16}}, {4,8}, {{1,2},{3,10},{12,16}}},
       {"T2", {{1,3},{6,9}}, {2,5}, {{1,5},{6,9}}},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.insert(input, newInterval) == expected);
    }
}
