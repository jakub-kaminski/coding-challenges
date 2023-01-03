// QUESTION NAME: DPX-Print Longest Increasing Subsequence
// DESCRIPTION: Given a vector nums
// https://takeuforward.org/data-structure/longest-increasing-subsequence-dp-41/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

struct S1 {
    vector<int> solve(v1t &nums) {
        v1t dp(nums.size(), 1);
        v1t hash(nums.size(), 0);
        int globalMax = 1;
        int globalMaxTail = 0;
        for (int i = 1; i < nums.size(); ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] > nums[j]) {
                    if(dp[j]+1 > dp[i]){
                        dp[i] = dp[j]+1;
                        hash[i] = j;
                    }
                }
            }
            if(dp[i] > globalMax){
                globalMax = dp[i];
                globalMaxTail = i;
            }
        }
        v1t res(globalMax, 0);
        int id = globalMaxTail;
        for(int k = 0; k < globalMax; ++k){
            res[globalMax-1-k] = nums[id];
            id = hash[id];
        }
        return res;
    }
};

// IMPLEMENTATION ENDS

//@formatter:off
TEMPLATE_TEST_CASE("Longest Increasing Subsequence", "", S1) {
    auto [msg, input, expected] =
            GENERATE(table<string, v1t, v1t>({
                                                     {
                                                             "T1",
                                                             {1, 2, 3},
                                                             {1, 2, 3}
                                                     },
                                                     {
                                                             "T2",
                                                             {1,  4, 0},
                                                             {1, 4}
                                                     },
                                                     {
                                                             "T3",
                                                             {1,  0, 3},
                                                             {0, 3}
                                                     },
                                                     {
                                                             "T4",
                                                             {1, 4, 1, 1, 5},
                                                             {1, 4, 5}
                                                     },
                                                     {
                                                             "T5",
                                                             {1,  4, 2, 3, 5},
                                                             {1, 2, 3, 5}
                                                     },
                                                     {
                                                             "T6",
                                                             {1,  4, 2, 3, 5, 4, 5},
                                                             {1, 2, 3, 4, 5}
                                                     },
                                                     {
                                                             "T7",
                                                             {8,  7, 6, 1, 4, 2, 3, 5, 4, 5},
                                                             {1, 2, 3, 4, 5}
                                                     },
                                                     {
                                                             "t8",
                                                             {10, 9, 2, 5, 3, 7, 1, 18},
                                                             {2, 3, 7, 18}
                                                     }
                                             }));

//@formatter:on

    TestType solver;
    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(input) == expected);
    }
}
