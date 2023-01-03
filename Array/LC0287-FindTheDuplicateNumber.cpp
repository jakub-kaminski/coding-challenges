#include <catch2/catch_all.hpp>

using namespace std;

typedef int out_type;
typedef std::vector<int> in_type;

//struct OptSolution {
//    out_type solve(in_type &vec) const;
//};

struct Opt_SumDiffSingleSolution {
    out_type solve(in_type &vec) const;
};

struct SubOpt_HashTableMultipleSolution {
    out_type solve(in_type &vec) const;
};

struct SubOpt_SortMultipleSolution {
    out_type solve(in_type &vec) const;
};

struct SubOpt_NegativeMarkingMultipleSolution {
    out_type solve(in_type &vec) const;
};

struct Opt_FloydMarkingMultipleSolution {
    out_type solve(in_type &vec) const;
};

//out_type OptSolution::solve(in_type &v) const {
//}

out_type Opt_SumDiffSingleSolution::solve(in_type &nums) const {
        int ref_len = nums.size() - 1;
        int ref_sum = ((1 + ref_len) * ref_len ) / 2;

        int sum = 0;

        for(auto it : nums){
            sum += it;
        }

        return sum - ref_sum;
    }

out_type SubOpt_SortMultipleSolution::solve(in_type &vec) const {
    std::sort(vec.begin(), vec.end());
    int prev = 0;
    for(auto it : vec){
        if(it == prev){
            return it;
        }
        prev = it;
    }
    return prev;
}

out_type SubOpt_HashTableMultipleSolution::solve(in_type &vec) const {
    std::unordered_map<int,int> map;
    for(auto it : vec){
        if(!map.count(it)){
            map[it] += 1;
        }
        else
        {
            return it;
        }
    }
}

// Credits: https://leetcode.com/problems/find-the-duplicate-number/solution/
out_type SubOpt_NegativeMarkingMultipleSolution::solve(in_type &vec) const {
    for (auto it : vec){
        if(vec[abs(it)] < 0){
            return abs(it);
        }
        vec[abs(it)] *= -1;
    }
    return 0;
}

// Credits: https://leetcode.com/problems/find-the-duplicate-number/solution/
out_type Opt_FloydMarkingMultipleSolution::solve(in_type &nums) const {
    // Find the intersection point of the two runners.
    int tortoise = nums[0];
    int hare = nums[0];

    do {
        tortoise = nums[tortoise];
        hare = nums[nums[hare]];
    } while (tortoise != hare);

    // Find the "entrance" to the cycle.
    tortoise = nums[0];
    while (tortoise != hare) {
        tortoise = nums[tortoise];
        hare = nums[hare];
    }
    return hare;
}

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Tests for Single Duplicate number approach", "[tag1]", Opt_SumDiffSingleSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type, out_type>({
            {"Array 1",  {1, 1, 2}, 1},
            {"Array 2",  {1, 5, 3, 2, 4, 2}, 2},
            {"Array 3",  {3,1,3,4,2}, 3}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        CHECK(solver.solve(input) == expected);
    }
}

TEMPLATE_TEST_CASE("Tests for Multiple Duplicate number approach", "[tag1]",
                   Opt_FloydMarkingMultipleSolution,
                   SubOpt_SortMultipleSolution,
                   SubOpt_HashTableMultipleSolution,
                   SubOpt_NegativeMarkingMultipleSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type, out_type>({
            {"Array 1",  {1, 4, 2, 2, 2, 3}, 2},
            {"Array 2",  {1, 5, 3, 2, 3, 4, 6, 3}, 3},
            {"Array 3",  {4,1,3,4,4,2}, 4}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(input) == expected);
    }
}
