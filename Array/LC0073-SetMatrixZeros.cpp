#include <catch2/catch_all.hpp>

class Solution {
public:
    virtual ~Solution() {}
    virtual void solve(vector<vector<int>>& matrix) const = 0;
};

class OptSolutionRefactor : public Solution {
public:
    virtual void solve(vector<vector<int>>& matrix) const override;
};

class OptSolution : public Solution {
public:
    virtual void solve(vector<vector<int>>& matrix) const override;
};

class Opt_SumSolution : public Solution {
public:
    virtual void solve(vector<vector<int>>& matrix) const override;
};

// 1 0 1 1 1
// 1 1 1 1 1
// 1 1 0 1 1
// 1 1 1 1 1
// 0 1 1 1 1

//Author: https://leetcode.com/v4vijay/
//Solution Link: https://leetcode.com/problems/set-matrix-zeroes/discuss/1276330/C++-or-Simple-or-99-Faster-or-O(1)-Space-or-Upvote
void OptSolutionRefactor::solve(vector<vector<int>> &a) const {
    int n = a.size();
    int m = a[0].size();
    bool firstRow = false;  // do we need to set first row zero
    bool firstCol = false;  // do we need to ser first col zero
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == 0){   // store rows and cols state in first row and col
                if(i==0) firstRow = true;
                if(j==0) firstCol = true;
                a[i][0] = 0;
                a[0][j] = 0;
            }
        }
    }
    // cout<<firstRow<<" "<<firstCol<<endl;
    for(int i=1; i<n; i++){
        for(int j=1; j<m; j++){
            if(a[i][0] == 0 || a[0][j] == 0){
                a[i][j] = 0;
            }
        }
    }

    if(firstRow){
        for(int i=0;i<m;i++) a[0][i] = 0;
    }

    if(firstCol){
        for(int i=0;i<n;i++) a[i][0] = 0;
    }
}


//void OptSolution::solve(vector<vector<int>> &m) const {
//    int col0 = 1, rows = m.size(), cols = m[0].size();
//    for (int r = 0; r < rows; r++) {
//        for (int c = 0; c < cols; c++) {
//            int r_tmp = r;
//            int c_tmp = c;
//            if (m[r][c] == 0) {
//                while (r_tmp >= 0) {
//                    m[r_tmp][c] = 0;
//                    r_tmp--;
//                }
//                while (c_tmp >= 0) {
//                    m[r][c_tmp] = 0;
//                    c_tmp--;
//                }
//            } else if (m[r][0] == 0) {
//                while (c_tmp >= 0) {
//                    m[r][c_tmp] = 0;
//                    c_tmp--;
//                }
//            } else if (m[0][c] == 0) {
//                while (r_tmp >= 0) {
//                    m[r_tmp][c] = 0;
//                    r_tmp--;
//                }
//            }
//        }
//    }
//}

void Opt_SumSolution::solve(vector<vector<int>> &matrix) const {
    bool populate_row0 = false;
    bool eraseColumn0 = !matrix[0][0];

    for (int r = 0; r < matrix.size(); ++r) {
        for (int c = 0; c < matrix[0].size(); ++c) {
            if (matrix[r][c] == 0) {
                if (c == 0) {
                    eraseColumn0 = true; // store info about row zeros
                } else {
                    matrix[0][c] = 0; // store info about row zeros
                }
                matrix[r][0] = 0; // store info about row zeros
            }
        }
    }


    for (int c = 1; c < matrix[0].size(); ++c) {
        if (matrix[0][c] == 0) {
            for (int r = 0; r < matrix.size(); ++r) {
                matrix[r][c] = 0;
            }
        }
    }


    for (int r = 0; r < matrix.size(); ++r) {
        if (matrix[r][0] == 0) {
            for (int c = 0; c < matrix[0].size(); ++c) {
                matrix[r][c] = 0;
            }
        }
    }

    if (eraseColumn0) {
        for (int r = 0; r < matrix.size(); ++r) {
            matrix[r][0] = 0;
        }
    }
}

typedef std::vector<std::vector<int>> io_type;

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("SetZeros", "", Opt_SumSolution) {
TEMPLATE_TEST_CASE("SetZeros", "", Opt_SumSolution, OptSolutionRefactor) {

//@formatter:off
    auto [msg, in, expected] = GENERATE(table<string, io_type, io_type>({
                                                                {"2x2 array",           {{1, 2},
                                                                                                {3, 0}},
                                                                                        {{1, 0},
                                                                                                {0, 0}}},
                                                                {"3x3 array",           {{1, 2, 3},
                                                                                                {3, 1, 0},
                                                                                                {2, 0, 1}},
                                                                                        {{1, 0, 0},
                                                                                                {0, 0, 0},
                                                                                                {0, 0, 0}}},
                                                                {"4x4 array",           {{1, 1, 1, 4},
                                                                                                {1, 0, 1, 1},
                                                                                                {1, 1, 0, 1},
                                                                                                {0, 0, 0, 1}},
                                                                                        {{0, 0, 0, 4},
                                                                                                {0, 0, 0, 0},
                                                                                                {0, 0, 0, 0},
                                                                                                {0, 0, 0, 0}}},
                                                                {"3x4 array (failing)", {{0, 1, 2, 0},
                                                                                                {3, 4, 5, 2},
                                                                                                {1, 3, 1, 5}},
                                                                                        {{0, 0, 0, 0},
                                                                                                {0, 4, 5, 0},
                                                                                                {0, 3, 1, 0}}},
                                                                {"3x5 array",           {{1, 2, 3, 4, 5},
                                                                                                {3, 0, 1, 2, 0},
                                                                                                {2, 0, 1, 1, 3}},
                                                                                        {{1, 0, 3, 4, 0},
                                                                                                {0, 0, 0, 0, 0},
                                                                                                {0, 0, 0, 0, 0}}}
                                                                        }
    )
    );
//@formatter:on

    TestType solver;
    SECTION("Testing:" + msg) {
        solver.solve(in);
        CHECK(in == expected);
        INFO("Current data input:" + msg);
    }
}
