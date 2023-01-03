#include <catch2/catch_all.hpp>

typedef std::vector<int> io_type;

//struct OptSolution {
//    io_type solve(io_type &vec) const;
//};

struct SubOptSolution {
    void solve(io_type &nums1, int m, io_type &nums2, int n) const;
};

void SubOptSolution::solve(io_type &nums1, int m, io_type &nums2, int n) const {
    int idx = m + n - 1;
    int a = m - 1;
    int b = n - 1;

    for(idx = m+n-1; idx >= 0; idx--){
        if(nums1[a] > nums2[b]){
            nums1[idx] = nums1[a];
            a--;
        } else{
            nums1[idx] = nums2[b];
            b--;
        }
    }

//    while (idx >= 0) {
//        while (a >= 0 && b >= 0 && idx >= 0 && nums1[a] >= nums2[b]) {
//            nums1[idx--] = nums1[a--];
//        }
//        if (idx <= 0) { return; }
//        while (a >= 0 && b >= 0 && idx >= 0 && nums2[b] >= nums1[a]) {
//            nums1[idx--] = nums2[b--];
//        }
//    }
}


//void SubOptSolution::solve(io_type &nums1, int m, io_type &nums2, int n) const {
//    int idx = m + n - 1;
//    int a = m - 1;
//    int b = n - 1;
//
//    while (idx >= 0) {
//        while (a >= 0 && b >= 0 && idx >= 0 && nums1[a] >= nums2[b]) {
//            nums1[idx--] = nums1[a--];
//        }
//        if (idx <= 0) { return; }
//        while (a >= 0 && b >= 0 && idx >= 0 && nums2[b] >= nums1[a]) {
//            nums1[idx--] = nums2[b--];
//        }
//    }
//}


// nums1
// ################## <-
// ##########################
// ############################
// ################################


//a[i]
//    |
//1 1 1 2 2 3 3 3 3 4 5 5
//        |
//idx
//
//b[k]
//|
//2 3 3 3 4
//
//

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge Intervals", "[tag1]", SubOptSolution) {
//@formatter:off
    auto [msg, nums1, m, nums2, n, expected] =
        GENERATE(table<string, io_type, int, io_type, int, io_type>({
        {"Elements 1",  {1, 4,5 , 0, 0}, 3, {1,5}, 2, {1,1,4,5,5}},
        {"Elements 2",  {3,4,5, 0, 0}, 3, {1,2}, 2, {1,2,3,4,5}},
        {"Elements 3",  {1,2,3,0,0,0}, 3, {2,5,6}, 3, {1,2,2,3,5,6}}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        solver.solve(nums1, m, nums2, n);
        CHECK(nums1 == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge Intervals", "[tag1]", SubOptSolution) {
//@formatter:off
    auto [msg, nums1, m, nums2, n, expected] =
            GENERATE(table<string, io_type, int, io_type, int, io_type>({
            {"Elements 1",  {1, 4,5 , 0, 0}, 3, {1,5}, 2, {1,1,4,5,5}},
            {"Elements 2",  {3,4,5, 0, 0}, 3, {1,2}, 2, {1,2,3,4,5}},
            {"Elements 3",  {1,2,3,0,0,0}, 3, {2,5,6}, 3, {1,2,2,3,5,6}}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        solver.solve(nums1, m, nums2, n);
        CHECK(nums1 == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}
