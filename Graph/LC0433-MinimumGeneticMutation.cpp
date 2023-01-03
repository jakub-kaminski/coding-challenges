// QUESTION NAME: LC0433 Minimum Genetic Mutation

// DESCRIPTION:
// A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.
//
// Suppose we need to investigate a mutation from a gene string start to a gene string end where one mutation
// is defined as one single character changed in the gene string.
//
// For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
// There is also a gene bank bank that records all the valid gene mutations.
// A gene must be in bank to make it a valid gene string.
//
// Given the two gene strings start and end and the gene bank bank, return
// the minimum number of mutations needed to mutate from start to end.
// If there is no such a mutation, return -1.
//
// Note that the starting point is assumed to be valid, so it might not be included in the bank.
//
// Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
// Output: 1
//
// Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
// Output: 2
//
// Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
// Output: 3
//
// start.length == 8
// end.length == 8
// 0 <= bank.length <= 10
// bank[i].length == 8
// start, end, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].
//
// https://leetcode.com/problems/minimum-genetic-mutation/

// APPROACH:
// Graph

// FUNCTION NAME: search

// TAGS:

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
    array<int, 8> encode(string s) {
        array<int, 8> res;
        string str = "ACGT";
        for (int i = 0; i < 8; ++i) res[i] = str.find(s[i]);
        return res;
    }

    array<int, 8> mut(array<int, 8> &in, int ind, int targetVal) {
        auto res = in;
        res[ind] = targetVal; //HINT: make sure to assign to a right value
        return res;
    }

public:
    int minMutation(string start, string end, vector <string> &bank) {
        set <array<int, 8>> valid;
        for (auto m: bank) valid.insert(encode(m));

        set <array<int, 8>> vis;

        queue < pair < array < int, 8 >, int >> q;
        vis.insert(encode(start));

        auto encEnd = encode(end);

        q.push({encode(start), 0});

        int steps = 0;

        while (!q.empty()) {
            auto [seq, stepNow] = q.front();
            q.pop();

            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 4; ++j) {
                    if (seq[i] != j) {
                        auto mutated = mut(seq, i, j);
                        if (valid.count(mutated) && !vis.count(mutated)) {
                            vis.insert(mutated);
                            steps = stepNow + 1;
                            if (mutated == encEnd) return steps;
                            q.push({mutated, stepNow + 1});
                        }
                    }
                }
            }
        }
        return -1;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Minumum number of Genetic Mutations", "[tag1]", Solution) {
//@formatter:off
auto [msg, startSequence, endSequence, mutationBank, expectedNumMutations] =
        GENERATE(table<string, string, string, vector<string>, int>({
               {"T1", "AACCGGTT", "AACCGGTA", {"AACCGGTA"}, 1},
//               {"T2", "AACCGGTT", "AAACGGTA", {"AACCGGTA","AACCGCTA","AAACGGTA"}, 2},
//               {"T3", "AAAAACCC", "AACCCCCC", {"AAAACCCC","AAACCCCC","AACCCCCC"}, 3},
       }));
//@formatter:on
TestType solver;

SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.minMutation(startSequence, endSequence, mutationBank) == expectedNumMutations);
}
}
