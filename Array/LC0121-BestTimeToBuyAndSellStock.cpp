#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int len = prices.size();
        int profit = 0;
        int buy = prices[0];

        for (int i = 1; i < len; ++i) {
            profit = max(profit, prices[i] - buy);
            buy = min(buy, prices[i]);
        }
        return profit;
    }
};


class OptSolution {
public:
    int maxProfit(vector<int> &prices) const {
        int minval = std::numeric_limits<int>::max();
        int gain = 0;

        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] < minval) {
                minval = prices[i];
                continue;
            }

            int tmp = prices[i] - minval;
            if (tmp > gain) {
                gain = tmp;
            }
        }
        return gain;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Stock Buy and Sell for Max Profit", "[tag1]", Solution, OptSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
            {"Short sequence, Gain possible",  {7,1,5,3,6,4}, 5},
            {"Short sequence, no gain",  {7,6,4,3,1}, 0},
            {"Short sequence with single trent inflection only",  {3,2,4}, 2}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.maxProfit(input) == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };
}
