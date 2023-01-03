#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    void fn(vector<int> &nums, vector<bool> available, int idx, vector<int> result_now, vector<vector<int>> &result){
        if(idx < 0){
            result.push_back(result_now);
            return;
        }
        for(int i = 0; i < nums.size(); ++i){
            if(available[i]){
                result_now.push_back(nums[i]);
                available[i]=false;
                fn(nums, available, idx-1, result_now, result);
            }
        }

    }
    vector<vector<int>> permute(vector<int>& nums) {
        int len = nums.size();
        vector<bool> available(len, true);
        vector<vector<int>> result{};
        vector<int> result_now{};
        fn(nums, available, len-1, result_now, result);
        return result;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("All permutations", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, vector<vector<int>>>({
            {"Sample set 1",  {0, 1}, {{1,0},{0,1}}},
            {"Sample set 2",  {1, 2, 3}, {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,2,1},{3,1,2}}},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.permute(input) == expected);
    }
}
