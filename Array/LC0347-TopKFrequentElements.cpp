// QUESTION NAME: LC0347 Top K Frequent Elements

// DESCRIPTION: implement heapify, max_heap, min_heap.
// https://leetcode.com/problems/top-k-frequent-elements/

// APPROACH:
// Heap

// FUNCTION NAME: topKFrequent

#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class SubOptSolution {
public:
    vector<int> topKFrequent(vector<int> &v,int k) {
        std::unordered_map<int, int> map;
        for (auto el: v) {
            if(!map.count(el))
                map[el] = 1;
            else
                map[el] += 1;
//            std::cout << map[el] << std::endl;
        }

        std::vector<std::vector<int>> f(v.size());

        for ( auto &it: map ) {
            f[it.second - 1].push_back(it.first);
//            std::cout << it.second << std::endl;
        }

        std::vector<int> res;
        int freq_p = v.size() - 1;
        while(f[freq_p].empty()) freq_p--;

        int i = 0;
        while(i < k){
            while(!f[freq_p].empty() && i<k){
                res.push_back(f[freq_p].back());
                f[freq_p].pop_back();
                i++;
            }
            --freq_p;
        }
        return res;
    }

};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Get Top k most frequent elements", "[tag1]", SubOptSolution) {
//@formatter:off
    auto [msg, input, k, expected] = GENERATE(table<string, vector<int>, int, vector<int>>({
            {"1 x 3 elements subsorted",  {1,1,1,2,2,3}, 2, {1, 2}},
            {"1 x 7 elements subsorted",  {5,3,1,1,1,3,73,1}, 1, {1}}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.topKFrequent(input, k);
        CHECK(result == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.topKFrequent(input); };
}