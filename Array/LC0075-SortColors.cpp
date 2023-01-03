#include <catch2/catch_all.hpp>

typedef void out_type;
typedef std::vector<int> in_type;

struct OptSolution {
    out_type solve(in_type &vec) const;
    void swap(int& a, int &b) const;
};

struct SubOptSolution {
    out_type solve(in_type &vec) const;
};

out_type OptSolution::solve(in_type &v) const {
    int min = 0;
    int mid = 0;
    int hi = v.size() - 1;
    while(mid <= hi){
        switch(v[mid])
        {
            case 0:
                swap(v[min++], v[mid++]);
                break;
            case 1:
                mid++;
                break;
            case 2:
                swap(v[mid], v[hi--]);
                break;
        }
    }
}

void OptSolution::swap(int& a, int &b) const{
    int tmp = a;
    a = b;
    b = tmp;
}

out_type SubOptSolution::solve(in_type &v) const {
    int len = v.size();
    int head = len - 1;
    int tail = 0;
    int foundTwos = 0;
    while (head > tail) {
        while (v[head] == 2) {
            foundTwos++;
            head--;
        }
        while (v[tail] != 2) { tail++; }
        if (head <= tail) { break; }
        int tmp = v[head];
        v[head] = v[tail];
        v[tail] = tmp;
    }

    tail = 0;
    head = len - 1 - foundTwos;
    while (head > tail) {
        while (v[head] == 1) { head--; }
        while (v[tail] != 1) { tail++; }
        if (head <= tail) { break; }
        int tmp = v[head];
        v[head] = v[tail];
        v[tail] = tmp;
    }
}

using std::string;

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Get max sum of subarray: Kadane's Algorithm", "[tag1]", OptSolution, SubOptSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type, in_type>({
            {"Vector of two zeros",  {0, 0}, {0, 0}},
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
