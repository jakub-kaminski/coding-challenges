#include <catch2/catch_all.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

typedef int out_type;
typedef std::vector<int> in_type;

//struct OptSolution {
//    out_type solve(in_type &v, int k) const;
//};
// 1 3 103 147 197 191  200
// 1 2 100 44  50 -6    9

struct OptSolution {
    out_type solve(in_type &v, int k){
        std::unordered_map<int,int> map;
//        map[0] = 0;
        int len = v.size();
        int sum = 0;
        int res = 0;
        for(int i = 0; i < len; ++i){
            sum += v[i];
            if(sum == k) res++;

            if(map.count(sum - k))
            {
                res+= map[sum -k];
            }
            map[sum] += 1;
//                map[sum] = 1;
        }
        return res;
    }
};


struct OptSolution2 {
    out_type solve(in_type &v, int k){
        std::unordered_map<int,int> map;
        map[0] = 1;
        int len = v.size();
        if(len == 1){
            return 1;
        }
        int sum = 0;
        int res = 0;
        for(int i = 0; i < len; ++i){
            sum += v[i];
//            if(sum == k) res++;

            if(map.count(sum - k))
            {
                res+= map[sum -k];
            }
            map[sum] += 1;
//                map[sum] = 1;
        }
        return res;
    }
};

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("Number of subarrays that equal k", "[tag1]", OptSolution) {
TEMPLATE_TEST_CASE("Number of subarrays that equal k", "[tag1]", OptSolution, OptSolution2) {
//@formatter:off
    auto [msg, input_array, target, expected] = GENERATE(table<string, in_type, int, out_type>({
            {"case 1",  {0, 1, 2, 3, 4, 5, -2}, 3, 4},
            {"case 2",  {1, 1, 1}, 2, 2},
            {"case 3",  {-1, 1, 0}, 0, 3},
            {"case 4",  {0,0,0,0,0,0,0,0,0,0}, 0, 55},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        CHECK(solver.solve(input_array, target) == expected);
    }
}
