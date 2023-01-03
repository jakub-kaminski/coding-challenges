#include <catch2/catch_all.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_set>

typedef std::vector<int> io_type;

using std::string;


struct SolutionHashmap {
    io_type solve(io_type& u, io_type& v) const{
        std::vector<int> res;
        std::unordered_set<int> set;
        for(auto& it : u){
            if(!set.contains(it))
                set.insert(it);
        }
        for(auto& it : v){
            if(set.contains(it)) {
                set.erase(it);
                res.push_back(it);
            }
        }
        return res;
    }
};

struct SolutionMerge {
    io_type solve(io_type& u, io_type& v) const{
        const int len1 = u.size();
        const int len2 = v.size();
        int i = 0;
        int j = 0;

        std::sort(u.begin(), u.end());
        std::sort(v.begin(), v.end());

        std::vector<int> res;

        while(i < len1 && j < len2){
            if(u[i] == v[j]){
                res.push_back(u[i]);
                i++;
                j++;
                while(i < len1 && u[i] == u[i-1]) i++;
                while(j < len2 && v[j] == v[j-1]) j++;
            }else if(u[i] < v[j]){
                i++;
            }else{
                j++;
            }
        }
        return res;
    }
};


//struct SolutionMerge {
//    io_type solve(io_type& u, io_type& v) const{
//        const int len1 = u.size();
//        const int len2 = v.size();
//        int i = 0;
//        int j = 0;
//
//        std::sort(u.begin(), u.end());
//        std::sort(v.begin(), v.end());
//
//        std::vector<int> res;
//
//        while(i < len1 && j < len2){
//            if(u[i] == v[j]){
//                res.push_back(u[i]);
//                i++;
//                j++;
//                while(i < len1 && u[i] == u[i-1]) i++;
//                while(j < len2 && v[j] == v[j-1]) j++;
//            }else if(u[i] < v[j]){
//                i++;
//            }else{
//                j++;
//            }
//        }
//        return res;
//    }
//};
//

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Intersection of two arrays", "[tag1]", SolutionHashmap, SolutionMerge) {
//@formatter:off
    auto [msg, input1, input2, expected] = GENERATE(table<string, io_type, io_type, io_type>({
            {"3 elements all intersecting",  {0, 1, 2}, {0, 1, 2}, {0, 1, 2}},
            {"3 elements no intersecting",  {0, 1, 2}, {3, 4, 5}, {}},
            {"3 elements one intersecting",  {0, 1, 2}, {4, 3, 2}, {2}},
            {"one intersecting, many times",  {1, 1, 1}, {1, 1, 1}, {1}},
            {"one intersecting, many times",  {1, 2, 2, 1}, {2, 2}, {2}},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(input1, input2) == expected);
    }
}
