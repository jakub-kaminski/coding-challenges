//credits: Suryansh Singh chauhan 8 godzin temu, YT Comments: https://www.youtube.com/watch?v=V0GNBkWYDaY

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        stack<int>s;
        int n=arr.size();
        vector<int>dp(n,0);
        int pre=-1;
        long long ans=0;
        int mod=1e9+7;
        for(int i=0;i<n;i++)
        {
            while(s.size()){
                if(arr[s.top()]>=arr[i]){
                    s.pop();
                }
                else break;
            }
            if(!s.size())pre=-1;
            else pre=s.top();
            s.push(i);
            if(pre==-1){
                dp[i]=((i+1)*arr[i])%mod;
            }
            else {
                dp[i]=(dp[pre]+((i-pre)*arr[i])%mod)%mod;
            }
            ans=(ans+dp[i])%mod;
        }
        return ans;
    }
};
