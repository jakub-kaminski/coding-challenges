// QUESTION NAME: ALG0001 Heap

// DESCRIPTION: implement heapify, max_heap, min_heap.
// https://www.geeksforgeeks.org/building-heap-from-array/
// https://www.geeksforgeeks.org/heap-using-stl-c/

// APPROACH:
// Heap i

// FUNCTION NAME: buildHeap

#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;


class Solution {
public:
    int heapSize;
    vector<int> vec;
    // To heapify a subtree rooted with node i which is
    // an index in vec[]. N is size of heap
    void heapify(int i) {
        int largest = i; // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < vec.size() && vec[l] > vec[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < vec.size() && vec[r] > vec[largest])
            largest = r;

        // If largest is not root
        if (largest != i) {
            swap(vec[i], vec[largest]);

            // Recursively heapify the affected sub-tree
            heapify(largest);
        }
    }

    // Function to build a Max-Heap from the given array
    vector<int> buildHeap(vector<int>& arr) {
        vec = arr;
        // Index of last non-leaf node
        int len = vec.size();
        heapSize = vec.size();
        int startIdx = (heapSize / 2) - 1;

        // Perform reverse level order traversal
        // from last non-leaf node and heapify
        // each node
        for (int i = startIdx; i >= 0; i--) {
            heapify(i);
        }
        return vec;
    }

    void perculateUp(int i){
        while(i>0 && vec[i/2] <vec[i]){
            swap(vec[i], vec[i/2]);
            i = i/2;
        }
    }

    void push(int val){
        if(heapSize < vec.size()){
            heapSize += 1;
            vec[heapSize-1] = val;
            perculateUp(heapSize-1);
        }
    }

    void pop(){
        if(heapSize > 0){
            swap(vec[0], vec[heapSize-1]);
            heapSize -= 1;
        }
        heapify(0);
    }

    vector<int> getHeap(){
        if(heapSize > 0){
            return {vec.begin(), vec.begin() + heapSize};
        }
    }

    int top(){
        return vec[0];
    }
};

// IMPLEMENTATION ENDS

// Binary Tree Representation
// of input array
//             1
//           /    \
//         3        5
//       /  \     /  \
//     4      6  13  10
//    / \    / \
//   9   8  15 17
vector<int> input1 = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};

// Final Heap:
//              17
//            /    \
//          15      13
//         /  \     / \
//        9     6  5   10
//       / \   / \
//      4   8 3   1
vector<int> expected1 = {17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1};

TEMPLATE_TEST_CASE("Build Max Heap", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE_COPY(table<string, vector<int>, vector<int>>({
        { "T1", input1, expected1}
    }));
//@formatter:on
    TestType solver;

    auto res = solver.buildHeap(input);
    SECTION(msg) {
        CAPTURE(msg);
        CAPTURE(input);
        CAPTURE(res);
        CHECK(res == expected);
    }

    SECTION(msg + "pop test") {
        CAPTURE(msg);
        CAPTURE(input);
        CAPTURE(res);
        solver.pop();
        CAPTURE(solver.getHeap());
        solver.pop();
        CAPTURE(solver.getHeap());
        solver.pop();
        solver.push(15);
        CAPTURE(solver.getHeap());
        CHECK(false == true);
        CHECK(res == expected);
    }
}