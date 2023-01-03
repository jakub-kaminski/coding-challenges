/// QUESTION NAME: LC0128 Longest Consecutive Sequence

// DESCRIPTION:
// Given an unsorted array of integers nums,
// return the length of the longest consecutive elements sequence.
// You must write an algorithm that runs in O(n) time.

//
// Input: nums = [100,4,200,1,3,2]
// Output: 4
// Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
// Therefore its length is 4.
// Input: nums = [0,3,7,2,5,8,4,6,0,1]
// Output: 9

// APPROACH:
//

// FUNCTION NAME: isPalindrome

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int longestConsecutive(vector<int>& v) const{
        std::unordered_map<int,int> map;
        for(auto i : v){
            map[i] += 1;
        }
        int max_len = 0;
        for(auto i: v){
            if(map.count(i-1))
                continue;

            int len_now = 0;
//            int n = 0;
            while(map.count(i+len_now)){
                len_now++;
                if (len_now > max_len)
                    max_len = len_now;
            }
        }
        return max_len;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Longest Consecutive Sequence", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
            {"Sample set 1",  {0, 11, 21, 22, 31, 32, 1, 2}, 3}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.longestConsecutive(input) == expected);
    }
}
