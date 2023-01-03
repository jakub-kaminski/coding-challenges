// QUESTION NAME: SBS0003 Check if number exists in sorted array

// DESCRIPTION:
// Return bool. use STL.
//
// https://youtu.be/edJ19qIL8WQ?list=PLgUwDviBIf0qYbL4TBaEWgb-ljVdhkM7R&t=294

// APPROACH:
//

// FUNCTION NAME: checkIfExists

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    static bool checkIfExists(vector<int> v, int t){
        return binary_search(v.begin(), v.end(), t);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Find the first occurence of element in ", "[tag1]", Solution) {
//@formatter:off
    auto [msg, v, t, expected] = GENERATE(table<string, vector<int>, int, bool>({
                                                                                       {"T1", {0,1,1,1,2,3,4,5,8,9,9}, 1, true},
                                                                                       {"T2", {0,1,1,1,2,3,4,5,8,9,9}, 8, true},
                                                                                       {"T3", {0,1,1,1,2,3,4,5,8,9,9}, 6, false},
                                                                                       {"T4", {0,1,1,1,2,3,4,5,8,9,9}, 10, false},
                                                                                       {"T5", {0,1,1,1,2,3,4,5,8,9,9}, -3, false},
                                                                               }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        auto result = solver.checkIfExists(v, t);
        CAPTURE(result);
        CHECK(result == expected);
    }
}

