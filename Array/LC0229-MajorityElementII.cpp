#include<catch2/catch_all.hpp>
#include<vector>

typedef std::vector<int> io_type;

struct Solution1{
    [[nodiscard]] io_type solve(const io_type& v) const{
        int len = v.size();
        int n1 = -1;
        int c1 = 0;
        int n2 = -1;
        int c2 = 0;
        for(int i =0; i < len; i++){
            if(n1 == v[i]){
                c1++;
            }else if(n2 == v[i]){
                c2++;
            }else if(c1 <= 0){
                n1 = v[i];
                c1 = 1;
            }else if(c2 <= 0){
                n2 = v[i];
                c2 = 1;
            }else{
                c1--;
                c2--;
            }
        }
        c1 = 0; c2 = 0;
//        c1, c2 = 0;
        for(int i =0; i < len; i++) {
            if(n1 == v[i]){
                c1++;
            }
            if(n2 == v[i]){
                c2++;
            }
        }
        io_type res;
        if (c1 > len/3) res.push_back(n1);
        if (c2 > len/3) res.push_back(n2);
        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Majority elements greater than 1/3 of collection.", "[tag1]", Solution1){
    //@formatter=off
    auto [msg, input, expected] = GENERATE(table<std::string, io_type, io_type>({
        {"4 Elements", {1,2,1,2}, {1,2}},
        {"5 Elements", {1,2,3,1,2}, {1,2}},
        {"5 Elements: Single only", {1,2,4,4,3}, {4}},
        {"10 Elements: Single only", {1,2,4,4,3,1,2,4,4,3}, {4}},
        {"4 Elements", {1,2,1,2}, {1,2}}
    }));
    //@formatter=on

    TestType s;
    SECTION(msg){
        CHECK(s.solve(input) == expected);
    }

}
