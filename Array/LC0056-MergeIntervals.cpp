/// QUESTION NAME: LC0056 Merge Intervals

// DESCRIPTION:
// Given an array of intervals where intervals[i] = [starti, endi],
// merge all overlapping intervals, and return an array of the non-overlapping intervals
// that cover all the intervals in the input.
//
// Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
// Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

// Input: intervals = [[1,4],[4,5]]
// Output: [[1,5]]
// Explanation: Intervals [1,4] and [4,5] are considered overlapping.
//
// 1 <= intervals.length <= 10^4
// intervals[i].length == 2
// 0 <= start_i <= end_i <= 10^4

// APPROACH:
//

// FUNCTION NAME: merge

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef std::vector<std::vector<int>> io_type;

//struct OptSolution {
//    io_type solve(io_type &vec) const;
//};

class SubOptSolution {
public:
    io_type merge(io_type &v) const {
        std::sort(v.begin(), v.end(),
                  [](const auto &a, const auto &b) {
                      return a[0] < b[0];
                  });
        io_type res{v[0]};
        for (int i = 1; i < v.size(); i++) {
            if (v[i][0] <= res.back()[1]) {
                res.back()[1] = (v[i][1] > res.back()[1]) ? v[i][1] : res.back()[1];
            } else {
                res.push_back(v[i]);
            }
        }
        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge Intervals", "[tag1]", SubOptSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, io_type, io_type>({
            {"2 sorted intervals",  {{1,4},{4,5}}, {{1,5}}},
            {"5 sorted intervals",  {{1,3},{2,6},{8,10},{15,18}}, {{1,6},{8,10},{15,18}}},
            {"Two intervals into one", {{1,4},{0,4}}, {{0,4}}},
            {"Two intervals into two", {{0,0},{1,4}}, {{0,0}, {1,4}}},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.merge(input) == expected);
    }
}