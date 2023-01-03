// QUESTION NAME: SDP0034 Wildcard Matching

// DESCRIPTION: check if wildcard string s1 matches string s2.
// https://www.codingninjas.com/codestudio/problems/wildcard-pattern-matching_701650

// APPROACH:
// Recursion, DP

// FUNCTION NAME: wildcardMatching

#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

struct Word{
    string val;
    int freq;
    Word(string v, int f){
        val = v;
        freq = f;
    }

    bool operator < (const Word& other) const {
        if (freq == other.freq){
            return val > other.val;
        }
        return (freq < other.freq);
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> umap;
        vector<Word> unique_words;

        for(auto& w : words){
            if(!umap.count(w)){
                Word tmp(w, 1);
                unique_words.push_back(tmp);
                umap[w] = unique_words.size()-1; //id of added Word
            }
            else {
                unique_words[umap[w]].freq += 1;
            }
        }
        sort(unique_words.begin(), unique_words.end());

        vector<string> res;
        res.reserve(k);
        int ulen = unique_words.size()-1;
        for(int i = ulen; i > ulen-k; --i){
            res.push_back(unique_words[i].val);
        }
        return res;
    }
};

void heapify(vector<Word>& v, int idx){
    int largest = idx;
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;

    if(v[l].val > v[largest].val)
        largest = r;

}

void buildHeap(vector<Word>& wordVec){
    int startIdx = ( wordVec.size() / 2 ) -1;

    for(int i = startIdx; i >= 0; --i){
        heapify(wordVec, i);
    }

}

class Solution2 {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int>m;
        for(auto& w : words){
            m[w]++;
        }

        struct Comp{
            bool operator()(pair<string, int> &a, pair<string, int> &b){
                return (a.second > b.second) || (a.second == b.second && a < b);
            }
        };

        using Node = pair<string,int>;
        priority_queue<Node, vector<Node>, Comp> pq;
        for(auto &p : m){
            pq.push(p);
            if(pq.size() > k) pq.pop();
        }
        vector<string> ans;
        while(!pq.empty()){
            ans.push_back(pq.top().first);
            pq.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

class Solution3 {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int>m;
        for(auto& w : words){
            m[w]++;
        }

        struct Comp{
            bool operator()(pair<string, int> &a, pair<string, int> &b){
                return (a.second < b.second) || (a.second == b.second && a > b);
            }
        };

        using Node = pair<string,int>;

        priority_queue<Node, vector<Node>, Comp> pq;
        for(auto &p : m){
            pq.push(p);
        }
        vector<string> ans;
        for(int i = 0; i < k; ++i){
            ans.push_back(pq.top().first);
            pq.pop();
        }
        return ans;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Top K Frequent Words", "[tag1]", Solution, Solution2, Solution3) {
//@formatter:off
    auto [msg, strVec, k, expected] = GENERATE(table<string, vector<string>, int, vector<string>>({
            { "T1", {"i","love","leetcode","i","love","coding"}, 2, {"i", "love"}},
            { "T2", {"i","love","leetcode","i","love","coding","i","love","leetcode","i","love","coding","i","love","leetcode","i","love","coding","i","love","leetcode","i","love","coding","i","love","leetcode","i","love","coding","i","love","leetcode","i","love","coding"}, 2, {"i", "love"}}
        }));
//@formatter:on
    TestType solver;

//    BENCHMARK("simple"){ return solver.topKFrequent(strVec,k); };

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.topKFrequent(strVec, k);
        CAPTURE(result);
        CHECK(result == expected);
    }
}