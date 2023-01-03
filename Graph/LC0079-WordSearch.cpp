//
// Created by jakub on 11/4/22.
//


[["A","B","C","E"],["S","F","E","S"],["A","D","E","E"]]
"ABCEFSADEESE"
true


[["C","A","A"],["A","A","A"],["B","C","D"]]
"AAB"
true

[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]
"ABCB"
false

class Solution {
private:
    bool inBounds(int r, int c, vector<vector<char>>& b){
        return r>=0 && c >=0 && r < b.size() && c < b[0].size();
    }

    bool fn(int r, int c, int idx, vector<vector<char>>& b, string& w, vector<vector<int>>& vis){
        if(!inBounds(r,c,b) || idx == w.size() || b[r][c] != w[idx] || vis[r][c]) return false;
        vis[r][c] = 1;
        if(idx == w.size()-1) return true;

        array<int,4> dr = {-1, 0, 1, 0};
        array<int,4> dc = {0, 1, 0, -1};

        for(int i = 0; i < 4; ++i){
            if(fn(r+dr[i], c+dc[i], idx+1, b, w, vis)) return true;
        }
        vis[r][c] = 0;

        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();


        for(int r = 0; r < rows; ++r){
            for(int c = 0; c < cols; ++c){
                vector<vector<int>> vis(rows, vector<int>(cols, 0));
                if(fn(r,c,0,board,word, vis)) return true;
            }
        }
        return false;
    }
};
