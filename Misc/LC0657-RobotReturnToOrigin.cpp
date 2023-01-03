// QUESTION NAME: LC0657 Robot Return to Origin

// DESCRIPTION:
// There is a robot starting at the position (0, 0), the origin, on a 2D plane.
// Given a sequence of its moves, judge if this robot ends up at (0, 0) after it completes its moves.
// You are given a string moves that represents the move sequence of the robot where moves[i]
// represents its ith move. Valid moves are 'R' (right), 'L' (left), 'U' (up), and 'D' (down).
// Return true if the robot returns to the origin after it finishes all of its moves, or false otherwise.
// Note: The way that the robot is "facing" is irrelevant. 'R' will always make the robot move to the right once,
// 'L' will always make it move left, etc. Also, assume that the magnitude
// of the robot's movement is the same for each move.
//
// Input: moves = "UD"
// Output: true
// Explanation: The robot moves up once, and then down once.
// All moves have the same magnitude, so it ended up at the origin where it started. Therefore, we return true.
//
// Input: moves = "LL"
// Output: false
// Explanation: The robot moves left twice. It ends up two "moves" to the left of the origin.
// We return false because it is not at the origin at the end of its moves.
//
// https://leetcode.com/problems/robot-return-to-origin/
//
// 1 <= moves.length <= 2 * 104
// moves only contains the characters 'U', 'D', 'L' and 'R'

// APPROACH:
//

// FUNCTION NAME: judgeCircle

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        unordered_map<char,int> m;
        for(auto c : moves){
            ++m[c];
        }
        if(m['R'] == m['L'] && m['U'] == m['D']) return true;
        else return false;
    }
};

// IMPLEMENTATION ENDS

//@formatter:off
TEMPLATE_TEST_CASE("Plus One", "[tag1]", Solution) {
    auto [msg, moves, expected] = GENERATE_COPY(table<string, string, bool>({
              {"T1", "RLUD", true},
              {"T2", "RLRUD", false},
              {"T3", "RLRUDUUDDL", true},
              {"T4", "", true},
              {"T5", "R", false},
              {"T6", "RL", true},
      }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.judgeCircle(moves) == expected);
    }
}
