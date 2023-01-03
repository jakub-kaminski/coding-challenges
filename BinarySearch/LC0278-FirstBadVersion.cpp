// QUESTION NAME: SBS0003 Check if number exists in sorted array

// DESCRIPTION:
// Given an array of integers nums which is sorted in ascending order, and an integer target,
// write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
// You must write an algorithm with O(log n) runtime complexity.

// https://leetcode.com/problems/binary-search/

// APPROACH:
//

// FUNCTION NAME: search

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

// You are a product manager and currently leading a team to develop a new product.
// Unfortunately, the latest version of your product fails the quality check.
// Since each version is developed based on the previous version, all the versions after a bad version are also bad.
//
// Suppose you have n versions [1, 2, ..., n] and you want to find out
// the first bad one, which causes all the following ones to be bad.
//
// You are given an API bool isBadVersion(version) which returns whether
// version is bad. Implement a function to find the first bad version.
// You should minimize the number of calls to the API.
//
// Input: n = 5, bad = 4
// Output: 4
// Explanation:
// call isBadVersion(3) -> false
// call isBadVersion(5) -> true
// call isBadVersion(4) -> true
// Then 4 is the first bad version.
//
// Input: n = 1, bad = 1
// Output: 1
//
// 1 <= bad <= n <= 231 - 1

class Solution {
public:
    int firstBadVersion(int n) {
        if(n == 1) return 1;
        if(!isBadVersion(n)) return n;

        long l = 1;
        long r = n;

        while(l <= r){ // HINT: the <= sign

            long mid = (l+r)/2;
            if(isBadVersion(int(mid))) r = mid-1;
            else{
                l = mid+1;
            }
        }
        return l;
    }
};


