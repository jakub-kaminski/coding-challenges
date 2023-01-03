// https://leetcode.com/problems/find-pivot-index/description/

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        if(nums.size() == 1) return 0;

        auto sumRight = nums;
        for(int i = nums.size()-2; i >= 0; --i){
            sumRight[i] += sumRight[i+1];
        }

        int sumLeft = 0;
        for(int i = 0; i < nums.size(); ++i){
            sumLeft += nums[i];
            if(sumLeft == sumRight[i]) return i;
        }


        return -1;
    }
};
