// QUESTION NAME: SBS0005 Find the smallest number greater than x in a sorted array

// DESCRIPTION:
// Return index. use STL. If not found return -1.
//
// https://youtu.be/edJ19qIL8WQ?list=PLgUwDviBIf0qYbL4TBaEWgb-ljVdhkM7R&t=294

// APPROACH:
//

// FUNCTION NAME: smallestGreaterThan

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    static int smallestGreaterThan(vector<int> v, int t){
        int ind = upper_bound(v.begin(), v.end(), t) - v.begin();
        if(ind != v.size()) return v[ind];
        else return -1;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Find the first occurence of element in ", "[tag1]", Solution) {
//@formatter:off
    auto [msg, v, t, expected] = GENERATE(table<string, vector<int>, int, int>({
                                                                                       {"T1", {0,1,1,1,2,3,4,5,8,9,9}, 0, 1},
                                                                                       {"T2", {0,1,1,1,2,3,4,5,8,9,9}, 8, 9},
                                                                                       {"T3", {0,1,1,1,2,3,4,5,8,9,9}, 6, 8},
                                                                                       {"T4", {0,1,1,1,2,3,4,5,8,9,9}, 10, -1},
                                                                                       {"T5", {0,1,1,1,2,3,4,5,8,9,9}, -3, 0},
                                                                                       {"T6", {0,1,1,1,2,3,4,5,8,9,9}, 1, 2},
                                                                               }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto result = solver.smallestGreaterThan(v, t);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
