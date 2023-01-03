#include<catch2/catch_all.hpp>
#include<vector>
#include<string>

//using std::string;

typedef std::vector<int> in_t;
typedef int out_t;

struct Solution1{
    out_t solve(in_t& v){
        int len = v.size();
        int sel = -1;
        int f = 0;

        for(int i = 0; i < len; i++){
            if(sel == v[i])
            {
                f++;
            }
            else
            {
                f--;
                if (f <= 0){
                    sel = v[i];
                    f = 1;
                }
            }
        }
        return sel;
     }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Find Majority Element","[tag1]", Solution1){
    auto [msg, in, expected] = GENERATE(table<std::string, in_t, out_t>({
        {"3 elements", {2,1,2}, 2},
        {"5 elements", {3,2,3,3,2}, 3}
    }));
    TestType s;
    SECTION(msg){
        CHECK(s.solve(in) == expected);
    }
}
