// QUESTION NAME: SBS0002 Find the last occurence of x in a sorted array

// DESCRIPTION:
// Return index. use STL. If not found return -1.
//
// https://youtu.be/edJ19qIL8WQ?list=PLgUwDviBIf0qYbL4TBaEWgb-ljVdhkM7R&t=294

// APPROACH:
// upper_bound() always points to the next greater element than the searched element.

// FUNCTION NAME: lastOccurrence

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    static int lastOccurrence(vector<int> v, int t){
        int ind = upper_bound(v.begin(), v.end(), t) - v.begin() - 1;
        // ind >= 0 protects if searched num is smaller than the first array num (when ind == -1)
        if(ind >= 0 && v[ind] == t) return ind;
        else return -1;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Find the first occurence of element in ", "[tag1]", Solution) {
//@formatter:off
    auto [msg, v, t, expected] = GENERATE(table<string, vector<int>, int, int>({
           {"T1", {0,1,1,1,2,3,4,5,8,9,9}, 1, 3},
           {"T2", {0,1,1,1,2,3,4,5,8,9,9}, 8, 8},
           {"T3", {0,1,1,1,2,3,4,5,8,9,9}, 6, -1},
           {"T4", {0,1,1,1,2,3,4,5,8,9,9}, 10, -1},
           {"T5", {0,1,1,1,2,3,4,5,8,9,9}, -3, -1},
           {"T6", {0,1,1,1,2,3,4,5,8,9,9}, 9, 10},
           {"T7", {4,5,8,9,9}, 3, -1},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto result = solver.lastOccurrence(v, t);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
