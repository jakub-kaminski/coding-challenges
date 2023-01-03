#include <catch2/catch_all.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef std::vector<int> io_type;

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

struct BubbleSort{
    void sort(io_type& v){
        int len = v.size();
        int i;

        for(i=0;i< len; i++){
            for(int j=1; j<len-i; j++){
                if(v[j] < v[j-1]){
                    swap(v[j], v[j-1]);
                }
            }
        }
    }

};

struct SelectionSort {
    void sort(io_type& v) const{
        int len = v.size();
        int i, j, k;
        for(i=0;i<len-1;i++){
            for(j=k=i; j < len; j++ ){
                if(v[j] < v[k]){
                    k = j;
                }
            }
            swap(v[i], v[k]);
//            int tmp = v[i];
//            v[i] = v[k];
//            v[k] = tmp;
        }
    }
};

struct InsertionSort {
    void sort(io_type& v) const{
        int len = v.size();

        for(int i = 1; i < len; i++){
            int j = i;
            while(j > 0 && v[j-1] > v[j]){
                swap(v[j-1], v[j]);
                j--;
            }
        }
    }
};

struct InsertionSortFaster {
    void sort(io_type& v) const{
        int len = v.size();

        for(int i = 1; i < len; i++){
            int x = v[i];
            int j = i-1;

            while(j > -1 && v[j] > x){
                v[j+1] = v[j];
                j--;
            }
            v[j+1] = x;
        }
    }
};

struct MergeSortIterative {
    void sort(io_type& v) const{
    }
    void merge(io_type& v, int l, int mid, int h){
        std::vector<int> res;
        res.reserve(h-l+1);

        int i,j,k;
        i = l; j=mid+1; k=l;
        while(i <= mid && j<=h){
            if(v[i] < v[j])
                res.push_back(v[i++]);
            else
                res.push_back(v[j++]);
        }
        for(;i<=mid;++i){
            res.push_back(v[i]);
        }
        for(;j<=h;++j){
            res.push_back(v[j]);
        }
        int n = 0;
        for(;l<=h;++l){
            v[l] = res[n];
            n++;
        }
    }
};

//struct QuickSort{
//    void sort(io_type& v) {
//        int q = v.size() -1;
//        int p = 0;
//        quick_sort(v, p, q);
//    }
//    void quick_sort(io_type& v, int start, int end) {
//        if(start >= end) return;
//
//        int p = start - 1;
//        int q = end + 1;
//        int pivot = v[(start + end) / 2];
//
//        while (true) {
//            while (pivot > v[++p]);
//            while (pivot < v[--p]);
//            if (p <= q)
//                swap(v[p], v[q]);
//            else
//                break;
//        }
//        if (q > start)
//            quick_sort(v, start, q);
//        if (p < end)
//            quick_sort(v, p, end);
//    }
//};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Sorting Algorithms", "[tag1]", BubbleSort, SelectionSort, InsertionSort, InsertionSortFaster) {
//@formatter:off
    auto [msg, input] = GENERATE(table<string, io_type>({
            {"5 elements sorted",  {0, 1, 2, 3, 4}},
            {"5 elements nearly sorted",  {2, 1, 0, 3, 4}},
            {"5 elements with repetitions sorted",  {2, 1, 1, 2, 4}},
            {"10 elements with repetitions sorted",  {2, 1, 1, 2, 4, 4, 5, 6, 7, 9}},
            {"10 elements with repetitions unsorted",  {4, 5, 6, 7, 9, 2, 1, 1, 2, 4}},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto expected = input;
        std::sort(expected.begin(), expected.end());

        solver.sort(input);
        CHECK(input == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}

TEMPLATE_TEST_CASE("Merging", "[tag1]", MergeSortIterative) {
//@formatter:of5 elements sortedf
    auto [msg, input] = GENERATE(table<string, io_type>({
        {"8 elements",  {4, 5, 6, 7, 0, 1, 2, 3}}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto expected = input;
        std::sort(expected.begin(), expected.end());

        int input_len = input.size();
        int mid = (0 + input_len - 1) / 2;
        solver.merge(input, 0, mid, input_len-1);
        CHECK(input == expected);
    }
}
