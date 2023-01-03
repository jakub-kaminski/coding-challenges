// QUESTION NAME: LC0890 Orderly Queue

// DESCRIPTION:
// You are given a string s and an integer k. You can choose one
// of the first k lettersof s and append it at the end of the string..
// Return the lexicographically smallest string you could have
// after applying the mentioned step any number of moves.
//
// Input: s = "cba", k = 1
// Output: "acb"
// Explanation:
// In the first move, we move the 1st character 'c' to the end, obtaining the string "bac".
// In the second move, we move the 1st character 'b' to the end, obtaining the final result "acb".
//
// Input: s = "baaca", k = 3
// Output: "aaabc"
// Explanation:
// In the first move, we move the 1st character 'b' to the end, obtaining the string "aacab".
// In the second move, we move the 3rd character 'c' to the end, obtaining the final result "aaabc".
//
// 1 <= k <= s.length <= 1000
// s consist of lowercase English letters.
//
// You take either ONE or TWO step up
// https://leetcode.com/problems/orderly-queue/

// APPROACH:
//

// FUNCTION NAME: orderlyQueue

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k > 1) {
            sort(s.begin(), s.end());
            return s;
        }

        queue<char> q;
        for (char c: s) q.push(c);

        auto minq = q;
        int bestShift = -1;

        int len = s.size();
        for (int i = 0; i < len; ++i) {
            char c = q.front();
            q.pop();
            q.push(c);

            if (q < minq) {
                minq = q;
                bestShift = i;
            }
        }

        if (bestShift != -1) {
            return s.substr(bestShift + 1, s.size() - bestShift - 1) + s.substr(0, bestShift + 1);
        }

        return s;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Word Search II", "[tag1]", Solution) {
//@formatter:off
    auto [msg, s, k, expected] = GENERATE(table<string, string, int, string>({
           {"T1",  "cba", 1, "acb"},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.orderlyQueue(s, k) == expected);
    }
}
