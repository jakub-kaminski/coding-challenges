// QUESTION NAME: SBS0004 Find the largest number smaller than x in a sorted array

// DESCRIPTION:
// Return index. use STL. If not found return -1.
//
// https://youtu.be/edJ19qIL8WQ?list=PLgUwDviBIf0qYbL4TBaEWgb-ljVdhkM7R&t=294

// APPROACH:
//

// FUNCTION NAME: largestSmallerThan

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    static int largestSmallerThan(vector<int> v, int t){
        int ind = lower_bound(v.begin(), v.end(), t) - v.begin() - 1;
        if(ind >= 0) return v[ind];
        else return -1;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Find the first occurence of element in ", "[tag1]", Solution) {
//@formatter:off
    auto [msg, v, t, expected] = GENERATE(table<string, vector<int>, int, int>({
           {"T1", {0,1,1,1,2,3,4,5,8,9,9}, 1, 0},
           {"T2", {0,1,1,1,2,3,4,5,8,9,9}, 8, 5},
           {"T3", {0,1,1,1,2,3,4,5,8,9,9}, 6, 5},
           {"T4", {0,1,1,1,2,3,4,5,8,9,9}, 10, 9},
           {"T5", {0,1,1,1,2,3,4,5,8,9,9}, -3, -1},
           {"T6", {0,1,1,1,2,3,4,5,8,9,9}, 0, -1},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto result = solver.largestSmallerThan(v, t);
        CAPTURE(result);
        CHECK(result == expected);
    }
}