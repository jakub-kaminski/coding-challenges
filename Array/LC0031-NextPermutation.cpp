#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

typedef void out_type;
typedef std::vector<int> in_type;

struct OptSolution {
    out_type solve(in_type &vec) const;
};

struct Opt_SumSolution {
    out_type solve(in_type &vec) const;
};

out_type OptSolution::solve(in_type &v) const {
    auto len = v.size();
    for (int i = len - 1; i > 0; i--) {
        if (v[i - 1] < v[i]) {
            int drop_val = v[i - 1];
            int k = len - 1;
            while (v[k] <= drop_val) {
                k--;
            }
            v[i - 1] = v[k];
            v[k] = drop_val;
            int tail = len - 1;
            for (int r = i; r < tail; r++) {
                int tmp = v[r];
                v[r] = v[tail];
                v[tail] = tmp;
                tail--;
            }
            return;
        }
    }
    std::sort(v.begin(), v.end());
}

out_type Opt_SumSolution::solve(in_type &v) const {
    int smallest = std::numeric_limits<int>::max(); //mind the order
    auto len = v.size(); //this is unsigned long
    int smallest_id = len - 1;
//    int smallest = v[len-1];
//    int smallest_id = len-1;
    for (int i = len - 1; i > 0; i--) {
        if (v[i] < smallest) {
            smallest = v[i];
            smallest_id = i;
        }
        if (v[i - 1] < v[i]) {
            int tmp = v[i - 1];
            v[i - 1] = smallest;
            v[smallest_id] = tmp;
            return;
        }
    }
    std::sort(v.begin(), v.end());
    return;
}

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("NextPermutation", "[tag1]", OptSolution, Opt_SumSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type , in_type>({
           {"1 Element",  {3}, {3}},
           {"2 Elements rising to front",  {2, 1}, {1, 2}},
           {"2 Elements descending to front",  {1, 2}, {2, 1}},
           {"3 Elements rising to front",  {3, 2, 1}, {1, 2, 3}},
           {"3 Elements descending to front", {1, 2, 3}, {1, 3, 2}},
           {"3 Elements checking for =< when repeating numbers in vector", {1, 5, 1}, {5, 1, 1}},
           {"3 Elements checking for =< when repeating numbers in vector", {1, 1, 5}, {1, 5, 1}},
           {"4 Elements (1)partially rising to front", {4, 2, 3, 1}, {4, 3, 1, 2}},
//           {"4 Elements (2)partially rising to front", {3, 4, 2, 1}, {4, 3, 2, 1}},
           {"4 Elements (3)partially rising to front", {1, 3, 2, 4}, {1, 3, 4, 2}},
           {"4 Elements descending to front", {1, 2, 3, 4}, {1, 2, 4, 3}},
           {"4 Elements drop close to the begin", {1, 4, 3, 2}, {2, 1, 3, 4}},
           {"4 Elements drop close to the begin large val", {6, 7, 5, 4}, {7, 4, 5, 6}},
           {"5 Elements partially rising to front", {5, 1, 4, 3, 2}, {5, 2, 1, 3, 4}},
           {"6 Elements rise and fall", {4, 5, 6, 3, 2, 1}, {4, 6, 1, 2, 3, 5}},
           {"6 Elements fall and rise", {6, 5, 4, 1, 2, 3}, {6, 5, 4, 1, 3, 2}}
   }));
//@formatter:on
    TestType solver;

    SECTION("Vectors: " + msg) {
//        TestType solver;
        solver.solve(input); //passed by reference

        INFO("Description of current input: " << msg);
        CAPTURE(msg);
        CHECK(input == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}

// begins:
// #############
// #######
// ##########
// #####
// ##


// begins:
// ##
// #####
// #######
// ##########
// #############

// ##
// #####
// #######
// #############
// ##########


// ##
// #####
// #######
// #############
// ##########


// ##
// #####
// ##########
// #############
// #######

// begins:
// #############
// #####
// #######
// ##########
// ##

// begins:
// #############
// #######
// ##########
// ##
// #####

// begins:
// #############
// ##
// ##########
// #######
// #####
// begins:
// #############
// #####
// ##########
// #######
// ##

// begins:
// #############
// #
// ##########
// ##
// #####

// ##
// #####
// #######
// ##########
// #############


// ##
// #####
// #######
// ##########
// #############

// #######
// ##########
// #############
// #####
// ##
//
