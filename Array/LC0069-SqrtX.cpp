// QUESTION NAME: LC0069 SQRT

// DESCRIPTION:
// Given a non-negative integer x, return the square root of x rounded down to the nearest integer.
// The returned integer should be non-negative as well.
//
// You must not use any built-in exponent function or operator.
// For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.
//
// Input: x = 4
// Output: 2
// Explanation: The square root of 4 is 2, so we return 2.
//
// Input: x = 8
// Output: 2
// Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.

// https://leetcode.com/problems/sqrtx/

// APPROACH:
//

// FUNCTION NAME: mySqrt

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

// credits: GoodTeacher https://www.youtube.com/watch?v=3MyA0dj-_2c
class SolutionBinary {
public:
    int mySqrt(int x) {
        if(x == 0) return 0;
        long start = 0;
        long end = x; // sqrt(INT_MAX)
        while(start+1 < end){
            long mid = start + (end-start) / 2;
            if(mid*mid == x) return mid;
            else if(mid*mid < x){
                start = mid;
            }
            else{
                end = mid;
            }
        }
        if(end*end == x) return end;
        return start;
    }
};

class Solution {
public:
    int mySqrt(int x) {
        if(x == 0) return 0;
        long side = 1;
        long area = 1;

        while(area <= x){
            area += 2 * side + 1;
            ++side;
        }
        return side-1;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Find floor sqrt of number", "[tag1]", SolutionBinary, Solution) {
//@formatter:off
auto [msg, num, expected] = GENERATE(table<string, int, int>({
    {"T1", 0, 0},
    {"T2", 1, 1},
    {"T3", 2, 1},
    {"T4", 3, 1},
    {"T5", 4, 2},
    {"T6", 5, 2},
    {"T7", 2147483647, 46340}, // INT_MAX
}));
//@formatter:on
TestType solver;

SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.mySqrt(num);
        CAPTURE(result);
        CHECK(result == expected);
}
}
