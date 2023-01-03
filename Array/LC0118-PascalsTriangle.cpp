#include <catch2/catch_all.hpp>

typedef std::vector<std::vector<int>> out_type;
typedef int in_type;


class OptSolution {
public:
//    virtual out_type solve(const in_type &numRows) const = delete;
    [[nodiscard]] int solveForSingleElement(std::tuple<const int&,const int&> idx) const;
    [[nodiscard]] out_type solve(const in_type &numRows) const;
};

class Opt_SumSolution {
public:
    [[nodiscard]] out_type solve(const in_type &numRows) const;
};

int OptSolution::solveForSingleElement(std::tuple<const int &, const int &> idx) const {
    auto [r, c] = idx; //decomposition declaration feature
    float tmp = 1;
    for (int i = 0; i < c; ++i) {
        tmp *= (r - i); // narrowing conversion from int to float
        tmp /= (i + 1); // narrowing conversion from int to float
    }
    return int(tmp);
}

out_type OptSolution::solve(const in_type &numRows) const {
    vector<vector<int>> r(numRows);

    for (int i = 0; i < numRows; i++) {
        r[i].resize(i + 1);
        r[i][0] = r[i][i] = 1;

        for (int j = 1; j < i; j++)
            r[i][j] = r[i - 1][j - 1] + r[i - 1][j];
    }

    return r;
}

out_type Opt_SumSolution::solve(const in_type &in) const {
    if (in == 0) { return out_type{{}}; }
    if (in == 1) { return out_type{{1}}; }

    out_type result{{{1}, {1, 1}}};
    if (in == 2) { return result; }

    for (int i = 2; i < in; ++i) {
        result.push_back({1});
        result[i].reserve(i + 1);
        for (int k = 1; k < i; ++k) {
            int val = result[i - 1][k - 1] + result[i - 1][k];
//            std::cout <<val <<std::endl;
            result[i].push_back(val);
        }
        result[i].push_back({1});
    }
    return result;
}

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("PascalsTriangle", "", OptSolution, Opt_SumSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type, out_type>({
        {"Second", 2, {{1}, {1, 1}}},
        {"Third",  3, {{1}, {1, 1}, {1, 2, 1}}},
        {"Forth",  4, {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}}}
    }));
//@formatter:on
    TestType solver;
    SECTION("Pascal's Triangle level: " + msg) {
        auto result = solver.solve(input);
        CHECK(result == expected);
    }
}

TEMPLATE_TEST_CASE("Pascals Benchmark", "", OptSolution, Opt_SumSolution) {
    auto bench_in = GENERATE(100,200,300);
    TestType solver;
    BENCHMARK("Timing for level: " + std::to_string(bench_in)){ return solver.solve(bench_in); };
}

TEMPLATE_TEST_CASE("Get single element value using [r,c] triangle indices", "", OptSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, std::tuple<int, int>, int>({
        {"Zeroth", {0, 0}, 1},
        {"First: Edge", {1, 1}, 1},
        {"Second: Mid", {2, 1}, 2},
        {"Third: Mid", {3, 2}, 3},
        {"Forth: Mid", {4, 2}, 6},
        {"Forth: Center-Lft", {4, 1}, 4},
        {"Forth: Center-Right", {4, 3}, 4}
    }));
//@formatter:on

    TestType solver;
    SECTION("Pascal's Triangle Single IDX: " + msg) {
        auto result = solver.solveForSingleElement(input);
        CHECK(result == expected);
    }
}
