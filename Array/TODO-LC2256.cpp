class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {
        int len = nums.size();
        vector<int> avgFront(len, 0);
        vector<int> avgBack(len, 0);

        // 1 2 3 4 //nums
        // 0 0 0 0 //avgFront

        long total = 0;
        for(int i = 0; i < len; ++i){
            total = total + nums[i];
            avgFront[i] = total / (i+1);
        }

        int k = 0;
        total = 0;
        for(int i = len-1; i >= 0; --i){
            total = total + nums[i];
            avgBack[i] = total / (k+1);
            ++k;
        }

        vector<int> absAverage(len, 0);

        for(int i = 0; i < len-1; ++i){
            absAverage[i] = abs(avgFront[i] - avgBack[i+1]);
        }
        absAverage[len-1] = avgFront[len-1];

        int minEl = INT_MAX;
        int minEl_idx = -1;

        for(int i = 0; i < len; ++i){
            if(absAverage[i] < minEl){
                minEl_idx = i;
                minEl = absAverage[i];
            }
        }

        return minEl_idx;
    }
};
