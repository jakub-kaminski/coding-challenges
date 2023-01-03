// QUESTION NAME: DPX-Knapsack
// DESCRIPTION: Put the most valuable stuff to backpack with limited capacity
// Each item has its value and weight (cost)

// APPROACH:
// Recursion, DP

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;

struct IS {
    string name;

    virtual ~IS() {};

    virtual int solve(vector<int>, vector<int>, int) = 0;
};

struct S1b : IS {
    explicit S1b(string s) { IS::name = s; }

    vector<int> vals;
    vector<int> kgs;

    int fn(int idx, int space) {
        if (space <= 0 || idx < 0) return 0;
        int pick = 0;
        if (kgs[idx] <= space) pick = vals[idx] + fn(idx - 1, space - kgs[idx]);
        int notPick = fn(idx - 1, space);
        return max(pick, notPick);
    }

    int solve(vector<int> v, vector<int> m, int space) override {
        int len = m.size();
        this->vals = v;
        this->kgs = m;
        return fn(len - 1, space);
    }
};

struct S2b : IS {
    vector<int> vals;
    vector<int> kgs;
    v2t dp;

    explicit S2b(string s) { IS::name = s; }

    int fn(int idx, int space) {
        if (space <= 0 || idx < 0) return 0;
        if (dp[idx][space] != -1) return dp[idx][space];

        int pick = 0;
        if (kgs[idx] <= space) pick = vals[idx] + fn(idx - 1, space - kgs[idx]);
        int notPick = fn(idx - 1, space);
        return dp[idx][space] = max(pick, notPick);
    }

    int solve(vector<int> v, vector<int> m, int space) override {
        int len = m.size();
        vals = v;
        kgs = m;
        dp = v2t(len, vector<int>(space + 1, -1));
        return fn(len - 1, space);
    }
};

struct S3b : IS {
    explicit S3b(string s) { IS::name = s; }

    vector<int> vals;
    vector<int> kgs;
    v2t dp;

    int solve(vector<int> v, vector<int> m, int space) {
        int len = m.size();
        vals = v;
        kgs = m;
        dp = v2t(len, vector<int>(space + 1, 0));
        for (int i = kgs[0]; i <= space; ++i) dp[0][i] = vals[0];

        for (int idx = 1; idx < len; ++idx) {
            for (int sp = 0; sp <= space; ++sp) {
                int pick = 0;
                if (kgs[idx] <= sp) pick = vals[idx] + dp[idx - 1][sp - kgs[idx]];
                int notPick = dp[idx - 1][sp];
                dp[idx][sp] = max(pick, notPick);
            }
        }

        return dp[len - 1][space];
//        return *max_element(dp[len-1].begin(), dp[len-1].end());
    }
};

struct S4b : IS {
    explicit S4b(string s) { IS::name = s; }

    vector<int> vals;
    vector<int> kgs;
    v2t dp;

    int solve(vector<int> v, vector<int> m, int space) {
        int len = m.size();
        vals = v;
        kgs = m;
        auto prev = vector<int>(space + 1, 0);
        auto curr = prev;
        for (int i = kgs[0]; i <= space; ++i) prev[i] = vals[0];

        for (int idx = 1; idx < len; ++idx) {
            for (int sp = 0; sp <= space; ++sp) {
                int pick = 0;
                if (kgs[idx] <= sp) pick = vals[idx] + prev[sp - kgs[idx]];
                int notPick = prev[sp];
                curr[sp] = max(pick, notPick);
            }
            prev = curr;
        }
        return prev[space];
//        return *max_element(dp[len-1].begin(), dp[len-1].end());
    }
};


struct S5b : IS {
    explicit S5b(string s) { IS::name = s; }

    vector<int> vals;
    vector<int> kgs;
    v2t dp;

    int solve(vector<int> v, vector<int> m, int space) {
        int len = m.size();
        vals = v;
        kgs = m;
        auto prev = vector<int>(space + 1, 0);
        for (int i = kgs[0]; i <= space; ++i) prev[i] = vals[0];

        for (int idx = 1; idx < len; ++idx) {
            for (int sp = space; sp >= 0; --sp) {
                int pick = 0;
                if (kgs[idx] <= sp) pick = vals[idx] + prev[sp - kgs[idx]];
                int notPick = prev[sp];
                prev[sp] = max(pick, notPick);
            }
        }
        return prev[space];
//        return *max_element(dp[len-1].begin(), dp[len-1].end());
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Classic Knapsack problem", "[tag1]", S1b, S2b, S3b, S4b, S5b) {

//@formatter:off
    auto [msg, vals, kgs, bag, expected] = GENERATE(table<string, vector<int>,vector<int>,int,int>({
                                                                                                  {
                                                                                                          "test1",
                                                                                                          {1,2,3}, //val
                                                                                                          {1,2,3}, //kg
                                                                                                          2, //bag
                                                                                                          2 //expected
                                                                                                  },

                                                                                                  {
                                                                                                          "test2",
                                                                                                          {3,2,3}, //val
                                                                                                          {2,1,1}, //kg
                                                                                                          3, //bag
                                                                                                          6 //expected
                                                                                                  },

                                                                                                  {
                                                                                                          "test3",
                                                                                                          {3,4}, //val
                                                                                                          {2,1}, //kg
                                                                                                          2, //bag
                                                                                                          4 //expected
                                                                                                  },

                                                                                                  {
                                                                                                          "test4",
                                                                                                          {3,4}, //val
                                                                                                          {2,1}, //kg
                                                                                                          20, //bag
                                                                                                          7 //expected
                                                                                                  },
    }));
//@formatter:on
    TestType solver("unused string");

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(vals, kgs, bag) == expected);
    }
}
