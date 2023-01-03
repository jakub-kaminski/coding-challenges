#include <catch2/catch_all.hpp>

typedef std::vector<int> io_type;

//struct OptSolution {
//    io_type solve(io_type &vec) const;
//};

struct SubOptSolution {
    io_type solve(io_type &vec) const;
};
//io_type OptSolution::solve(io_type &v) const {
//}

io_type SubOptSolution::solve(io_type &v) const {
    std::unordered_map<int,int> map;
    int duplicate = 0;
    int missing = 0;
    for(auto it : v)
    {
        if(map.count(it)){
            duplicate = it;
        }
        map[it] += 1;
    }
    for (auto r=0; r < v.size(); r++){
        if(!map.count(r)){
            missing = r;
        }
    }
    return {duplicate,missing};
}

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Get max sum of subarray: Kadane's Algorithm", "[tag1]", SubOptSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type, in_type>({
            {"1 x 3 elements subsorted",  {0, 1, 2}, {0, 1, 2}},
            {"2 x 3 elements subsorted",  {0, 1, 2, 0, 1, 2}, {0, 0, 1, 1, 2, 2}},
            {"2 x 3 elements mixed",  {2, 0, 1, 0, 2, 1}, {0, 0, 1, 1, 2, 2}}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        solver.solve(input);
        CHECK(input == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}
