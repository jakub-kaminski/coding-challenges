#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

//void swap(int& a, int& b){
//    int tmp = a;
//    a = b;
//    b = tmp;
//}

class Solution{
private:
    int fn(int l, int r, int k, vector<int>& v){
        int pivot = v[r];
        int p = l;
        for(int i = l; i < r; ++i){
            if(v[i] <= pivot){
                swap(v[i], v[p]);
                p += 1;
            }
        }
        swap(v[p], v[r]);
        if(p>k) return fn(l, p-1, k, v);
        if(p<k) return fn(p+1, r, k, v);
        if(p==k) return v[p];
    }

public:
    int quickSelect(vector<int>& v, int k){
        int len = v.size();
        return fn(0,len-1,k, v);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("QuickSelect", "[tag1]", Solution) {
//@formatter:off
    auto [msg, vec, target, expected] = GENERATE(table<string, vector<int>, int, int>({
           {"T1",  {8,6,7,5}, 3, 8}, // sort element at the index 3 (the last one) and return this element
           {"T2",  {8,6,7,5}, 2, 7}, // sort element at the index 2 (second to last) and return this element
           {"T3",  {8,6,7,5}, 1, 6}, // sort element at the index 1 and return this element
           {"T4",  {8,6,7,5}, 0, 5}, // sort element at the index 0 and return this element
           {"T5",  {3,1,1,1,1,1,1,4,5,2,4}, 7, 3}, // sort element at the index 7 and return this element

   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.quickSelect(vec, target) == expected);
    }
}


//int main() {
////    vector<int> a = {1,2,3,4,4,5};
////     vector<int> a = {7, 10, 4, 3, 20, 15};
//    vector<int> a = {3,1,1,1,1,1,1,4,5,2,4};
////    int k = 4;
////    int k = 4;
////    int k = a.size()-4;
//    int k = 7;
//    int res = quickSelect(a, k);
//    cout << res << endl;
//    for(auto& el : a)
//        cout << el << " ";
//    cout <<endl;
//}


