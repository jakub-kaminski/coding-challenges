#include <catch2/catch_all.hpp>

typedef std::string out_type;
typedef int in_type;

struct Opt_HashMapSolution {
    out_type solve(in_type &num) const;
};

struct SubOptSolution {
    out_type solve(in_type &num) const;
};

using namespace std;

out_type Opt_HashMapSolution::solve(in_type &v) const {
     static std::unordered_map<int, std::string> map{{0,  "FizzBuzz"},
                                             {3,  "Fizz"},
                                             {5,  "Buzz"},
                                             {6,  "Fizz"},
                                             {9,  "Fizz"},
                                             {10, "Buzz"},
                                             {12, "Fizz"}
    };

    if(map.count(v % 15))
    {
        return map[v % 15];
    } else
    {
        return std::to_string(v);
    }
}

// fb    f   b f     f  b    f
// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14

out_type SubOptSolution::solve(in_type &v) const {
    std::string result = "";

    if (!(v % 3)) {
        result = "Fizz";
    }
    if (!(v % 5)) {
        result += "Buzz";
    }
    if(result.empty()){
        result = std::to_string(v);
    }
    return result;
}

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("FizzBuzz", "[tag1]", Opt_HashMapSolution, SubOptSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type, out_type>({
            {"Divided by 3",  3, "Fizz"},
            {"Divided by 3",  33, "Fizz"},
            {"Divided by 5",  5, "Buzz"},
            {"Divided by 5",  55, "Buzz"},
            {"Divided by 3 and 5",  15, "FizzBuzz"},
            {"Divided by 3 and 5",  30, "FizzBuzz"},
            {"Regular",  31, "31"},
            {"Regular",  37, "37"}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(input) == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}
