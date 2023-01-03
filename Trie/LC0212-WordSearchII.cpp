// QUESTION NAME: LC0212 Word Search II

// DESCRIPTION:
// Given an m x n board of characters and a list of strings words, return all words on the board.
// Each word must be constructed from letters of sequentially adjacent cells,
// where adjacent cells are horizontally or vertically neighboring.
// The same letter cell may not be used more than once in a word.
//
// Input: board = [["o","a","a","n"],
//                 ["e","t","a","e"],
//                 ["i","h","k","r"],
//                 ["i","f","l","v"]],
// words = ["oath","pea","eat","rain"]
// Output: ["eat","oath"]
//
// Input: board = [["a","b"],["c","d"]],
// words = ["abcb"]
// Output: []

// You take either ONE or TWO step up
// https://leetcode.com/problems/word-search-ii/

// APPROACH:
//

// FUNCTION NAME: findWords

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Node {
public:
    Node *alp[26];
    bool isEnd;
};

class Trie {
public:
    Node *root;

    Trie() { root = new Node(); }

    void addWord(string s) {
        Node *node = root;
        for (char c: s) {
            if (!node->alp[c - 'a']) {
                node->alp[c - 'a'] = new Node();
            }
            node = node->alp[c - 'a'];
        }
        node->isEnd = true;
    }

//    void addWord(string s) { // BAD!
//        Node *node = root;
//        for(int i = 0; i <s.size(); ++i){
//            if (!node->alp[s[i] - 'a']) {
//                node->alp[s[i] - 'a'] = new Node();
//            }
//            if(i == s.size()-1) node->isEnd = true;
//            node = node->alp[s[i] - 'a'];
//        }
//    }
};

class Solution {
private:
    bool inBounds(int r, int c, vector<vector<char>> &b) {
        return r >= 0 && c >= 0 && r < b.size() && c < b[0].size();
    }

    void fn(int r, int c, Node *node, string &strNow, unordered_set<string> &st, vector<string> &res,
            vector<vector<char>> &b, vector<vector<int>> &vis) {
        if (!inBounds(r, c, b) || node == nullptr || vis[r][c]) return;


        char charNow = b[r][c];
        if (node->alp[b[r][c] - 'a']) {
            vis[r][c] = 1;
            strNow.push_back(b[r][c]);
            if (node->alp[b[r][c] - 'a']->isEnd && !st.count(strNow)) {
                st.insert(strNow);
                res.push_back(strNow);
            }

            array<int, 4> dr = {-1, 0, 1, 0};
            array<int, 4> dc = {0, 1, 0, -1};

            for (int i = 0; i < 4; ++i) {
                fn(r + dr[i], c + dc[i], node->alp[b[r][c] - 'a'], strNow, st, res, b, vis);
            }
            vis[r][c] = 0;
            strNow.pop_back();
        }
    }

public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
        int rows = board.size();
        int cols = board[0].size();

        Trie trie{};
        for (string w: words) {
            trie.addWord(w);
        }

        unordered_set<string> st;
        vector<string> res;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                Node *node = trie.root;
                string strNow = "";
                vector<vector<int>> vis(rows, vector<int>(cols, 0));
                fn(r, c, node, strNow, st, res, board, vis);
            }
        }
        return res;
    }
};

// IMPLEMENTATION ENDS

vector<vector<char>> board1 = {{'o', 'a', 'a', 'n'},
                               {'e', 't', 'a', 'e'},
                               {'i', 'h', 'k', 'r'},
                               {'i', 'f', 'l', 'v'}
};
vector<string> words1 = {"oath", "pea", "eat", "rain"};
vector<string> expected1 = {"eat", "oath"};

vector<vector<char>> board2 = {{'a', 'b'},
                               {'c', 'd'}
};
vector<string> words2 = {"abcb"};
vector<string> expected2 = {};

vector<vector<char>> board3 = {{'o', 'a', 'a', 'n'},
                               {'e', 't', 'a', 'e'},
                               {'i', 'h', 'k', 'r'},
                               {'i', 'f', 'l', 'v'}
};
vector<string> words3 = {"oath", "pea", "eat", "rain", "hklf", "hf"};
vector<string> expected3 = {"oath", "eat", "hklf", "hf"};


TEMPLATE_TEST_CASE("Word Search II", "[tag1]", Solution) {
//@formatter:off
    auto [msg, board, words, expected] = GENERATE_COPY(table<string, vector<vector<char>>, vector<string>, vector<string>>({
           {"T1",  board1, words1, expected1},
//           {"T2",  board2, words2, expected2},
           {"T3",  board3, words3, expected3},
   }));
//@formatter:on
    TestType solver;
    auto wordsResult = solver.findWords(board, words);

    set<string> wordsResultSet;
    for(auto w : wordsResult) wordsResultSet.insert(w);

    set<string> wordsExpectedSet;
    for(auto w : expected) wordsExpectedSet.insert(w);

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(wordsResultSet == wordsExpectedSet);
    }
}
