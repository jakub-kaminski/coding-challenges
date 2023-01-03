class Solution {
    int fn(int r, int c, vector<vector<int>>& matrix, vector<vector<int>>& dp){
        if(r < 0) return 0;
        if(c < 0 || c >= matrix[0].size()) return INT_MAX;

        if(dp[r][c] != INT_MIN) return dp[r][c];

        array<int, 3> arr = {fn(r-1, c-1, matrix, dp), fn(r-1, c, matrix, dp), fn(r-1, c+1, matrix, dp)};
        return dp[r][c] = matrix[r][c] + *min_element(arr.begin(), arr.end());
    }
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<vector<int>> dp(rows, vector<int>(cols, INT_MIN));
        vector<int> resLastRow;
        resLastRow.reserve(cols);
        for(int i = 0; i < cols; ++i){
            resLastRow.push_back(fn(rows-1, i, matrix, dp));
        }
        return *min_element(resLastRow.begin(), resLastRow.end());
    }
};

class SolutionTab {
    int parentMin(int id, vector<int> & v){
        int mi = INT_MAX;
        for(int i = id-1; i <= id+1; ++i){
            if(i < 0 || i >= v.size()) continue;
            mi = min(mi, v[i]);
        }
        return mi;
    }
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int colSize = matrix[0].size();
        int rowSize = matrix.size();
        int mi = INT_MAX;
        if(rowSize == 1){
            return *min_element(matrix[0].begin(), matrix[0].end());
            // for(auto el : matrix[0]) mi = min(mi, el);
            // return mi;
        }

        vector<int> prevRow = matrix[0];
        for(int i = 1; i < rowSize; ++i){
            vector<int> nextRow = matrix[i];
            for(int j = 0; j < colSize; ++j) nextRow[j] += parentMin(j, prevRow);
            prevRow = nextRow;
        }

        return *min_element(prevRow.begin(), prevRow.end());
    }
};
