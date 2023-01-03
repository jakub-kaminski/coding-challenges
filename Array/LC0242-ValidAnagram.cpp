#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;

        vector<int> m(26,0);
        for(auto& el : s)
            m[int(el) - int('a')] += 1;

        for(auto& el : t){
            m[int(el) - int('a')] -= 1;
            if(m[int(el) - int('a')] < 0) return false;
        }
        return true;
    }
};

class Solution2 {
public:
    bool isAnagram(string s, string t) {
        vector<int> m(26,0);
        for(auto& el : s)
            m[int(el) - int('a')] += 1;

        for(auto& el : t){
            m[int(el) - int('a')] -= 1;
            if(m[int(el) - int('a')] < 0) return false;
        }
        for(auto& el : m)
            if(el != 0) return false;
        return true;
    }
};

class Solution1 {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t ;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Is valid anagram", "[tag1]", Solution, Solution1, Solution2) {
//@formatter:off
    auto [msg, s1, s2, expected] = GENERATE(table<string, string, string, bool>({
            {"T1", "a", "a", true},
            {"T1", "ab", "a", false},
            {"T2", "ab", "ba", true}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.isAnagram(s1, s2);
//        CAPTURE(solver.res);
        CHECK(result == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}
