// QUESTION NAME: LC0190 Number of 1 Bits

// DESCRIPTION:
// Reverse bits of a given 32 bits unsigned integer.
//
// Input: n = 00000010100101000001111010011100
// Output:    964176192 (00111001011110000010100101000000)
// Explanation: The input binary string 00000010100101000001111010011100
// represents the unsigned integer 43261596, so return 964176192
// which its binary representation is 00111001011110000010100101000000.

// https://leetcode.com/problems/reverse-bits/

// APPROACH:
//

// FUNCTION NAME: reverseBits

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {

        int res = 0;
        for(int i = 31; i >= 0; --i){
            res = res | ((n & 1) << i);
            n = n >> 1;
        }
        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Reverse Bits", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, int, int>({
           {"T1",  43261596, 964176192},
           {"T2",  4294967293, 3221225471}
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.reverseBits(input) == expected);
    }
}


