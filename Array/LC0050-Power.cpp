#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using std::string;

typedef double out_t;
typedef double in_t1;
typedef int in_t2;

//struct OptSolution {
//    out_t solve(in_t1 base, in_t2 pow) const;
//};

struct OptSolution2 {
    out_t solve(in_t1 base, in_t2 pow) const;
};

struct SubOptSolution {
    out_t solve(in_t1 base, in_t2 pow) const;
};

out_t SubOptSolution::solve(in_t1 base, in_t2 pow) const{
    if (pow == 0)
    {
        return 1;
    }
    double res = 1.0;
    for(int i = 0; i < pow; i++)
    {
        res *= base;
    }
    if(pow % 2 && base < 0)
    {
        return 1.0 / res;
    }
    return res;
}

//out_t OptSolution::solve(in_t1 base, in_t2 p) const{
//    if (p == 0)
//    {
//        return 1;
//    }
//    if (p == 1)
//    {
//        return base;
//    }
//
//    bool isNegative = false;
//    if(p < 0){
//        isNegative = true;
//        p *= -1;
//    }
//    double res = 1.0;
//     //odd
//    bool isOdd = false;
//    if(p % 2)
//    {
//        p--;
//        isOdd = true;
//    }
//
//    while(!(p%2)){
//        p /= 2;
//        res *= base * base;
//    }
//    for(int i = 1; i < p; i++)
//    {
//        res *= base;
//    }
//    if(isOdd){
//        res *= base;
//        }
//    if(isNegative){
//        res = 1/res;
//    }
//    return res;
//}

// 29 -##> 28 -> 14 -> 7 -##>  6 -> 3 -##> 2 -> 1
// ((2 * 2 * 2) + 1 ) * 2 * 2 + 1
//out_t OptSolution2::solve(in_t1 base, in_t2 p) const{
//    if (p == 0)
//    {
//        return 1;
//    }
//    if (p == 1)
//    {
//        return base;
//    }
//
//    bool isNegative = false;
//    if(p < 0){
//        isNegative = true;
//        p *= -1;
//    }
//    double res = 1.0;
//    //odd
//    bool isOdd = false;
//    if(p % 2)
//    {
//        p--;
//        isOdd = true;
//    }
//    label:
//    while(!(p%2)){
//        p /= 2;
//        res *= base * base;
//    }
//
//    while(p > 1)
//    {
//        p--;
//        if(!(p%2) && p > 0){
//            goto label;
//        }
//        res *= base;
//    }
//    if(isOdd){
//        res *= base;
//    }
//    if(isNegative){
//        res = 1/res;
//    }
//    return res;
//}


out_t OptSolution2::solve(in_t1 n, in_t2 k) const {
    double ans = 1.0;
    int dir = -1;
    bool invert = false;
    if(k < 0){
        dir = 1;
        invert = true;
    }
    while (k != 0) {
        if (k % 2 == 0) {
            n = n * n;
            k /= 2;
        } else {
            ans = ans * n;
            k = k + dir;
        }
    }
    if(invert){
        ans = 1.0 / ans;
    }
    return ans;
}

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("Pow(num,pow)","[tag1]", SubOptSolution){
TEMPLATE_TEST_CASE("Pow(num,pow)","[tag1]", OptSolution2, SubOptSolution){
//TEMPLATE_TEST_CASE("Pow(num,pow)","[tag1]", OptSolution, OptSolution2, SubOptSolution){
    //@formatter=off
    auto [msg, num, p, expected] = GENERATE(table<string, in_t1, in_t2, out_t>({
//        {"2^0", 2.0, 0, 1.0},
//        {"2^1", 2.0, 1, 2.0},
//        {"2^2", 2.0, 2, 4.0},
//        {"Large num 1", 2.0, 14, 4.0},
//        {"Large num 2", 2.0, 11, 4.0},
//        {"Large num 2", 2.0, 10, 4.0},
        {"Even Negative pow 2^-2", 2.0, -2, 1.0/4.0},
        {"Odd Negative pow 2^-3", 2.0, -3, 1.0/-8.0},
        {"Base number smaller than 1. 0.5^2", 0.5, 2, 0.25}
    }));

    TestType solver;
    SECTION(msg){
        CAPTURE(solver.solve(num,p), pow(num,p));
        double res_diff = abs(solver.solve(num,p) - pow(num,p));
        CHECK(res_diff < 0.001);
    }
    //@formatter=on
}
