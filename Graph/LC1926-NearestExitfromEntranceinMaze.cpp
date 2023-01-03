// QUESTION NAME: LC1926 Nearest Exit from Entrance in Maze


// DESCRIPTION:
// You are given an m x n matrix maze (0-indexed) with empty cells (represented as '.')
// and walls (represented as '+'). You are also given the entrance of the maze,
// where entrance = [entrancerow, entrancecol] denotes the row and
// column of the cell you are initially standing at.
//
// In one step, you can move one cell up, down, left, or right.
// You cannot step into a cell with a wall, and you cannot step
// outside the maze. Your goal is to find the nearest exit from the entrance.
// An exit is defined as an empty cell that is at the border of the maze.
// The entrance does not count as an exit.
//
// Return the number of steps in the shortest path from
// the entrance to the nearest exit, or -1 if no such path exists.
//
// Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
// Output: 1
// Explanation: There are 3 exits in this maze at [1,0], [0,2], and [2,3].
// Initially, you are at the entrance cell [1,2].
// - You can reach [1,0] by moving 2 steps left.
// - You can reach [0,2] by moving 1 step up.
// It is impossible to reach [2,3] from the entrance.
// Thus, the nearest exit is [0,2], which is 1 step away.
//
// Input: maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
// Output: 2
// Explanation: There is 1 exit in this maze at [1,2].
// [1,0] does not count as an exit since it is the entrance cell.
// Initially, you are at the entrance cell [1,0].
// - You can reach [1,2] by moving 2 steps right.
// Thus, the nearest exit is [1,2], which is 2 steps away.
//
// https://leetcode.com/problems/spiral-matrix/

// APPROACH:
//

// FUNCTION NAME: nearestExit

// TAGS:

#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int rows = maze.size();
        int cols = maze[0].size();

        queue<array<int,3>> q;
        array<int,3> ent = {entrance[0], entrance[1], 0};
        q.push(ent);

        vector<vector<int>> vis(rows, vector<int>(cols, 0));

        while(!q.empty()){
            auto [r, c, cost] = q.front();
            q.pop();
            if(vis[r][c]) continue;

            vis[r][c] = 1;

            if(r == 0 || r == rows-1 || c == 0 || c == cols-1){
                if(ent[0] != r || ent[1] != c) return cost;
            }

            array<int,4> dr = {-1,0,1,0};
            array<int,4> dc = {0,1,0,-1};

            for(int i = 0; i < 4; ++i){
                int rn = r + dr[i];
                int cn = c + dc[i];
                if(rn < 0 || rn == rows || cn < 0 || cn == cols) continue;
                if(maze[rn][cn] != '+' && !vis[rn][cn]){
                    q.push({rn, cn, cost + 1});
                }
            }
        }
        return -1;
    }
};