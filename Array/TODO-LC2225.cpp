// two hashmaps
class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
       unordered_map<int,int> winners;
       unordered_map<int,int> losers;

        for(vector<int> match : matches){
            ++winners[match[0]];
            ++losers[match[1]];
        }

        vector<int> ansA;
        vector<int> ansB;
        for(auto el : winners){
            if(losers.count(el.first) == 0) ansA.push_back(el.first);
        }

        for(auto el : losers){
            if(el.second == 1) ansB.push_back(el.first);
        }

        sort(ansA.begin(),ansA.end());
        sort(ansB.begin(),ansB.end());

        return {ansA, ansB};
    }
};

// single hashmap
class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        unordered_map<int,int> played;

        for(vector<int> m : matches){
            if(!played.count(m[0])) played[m[0]] = 0;
            ++played[m[1]];
        }

        vector<int> ansA;
        vector<int> ansB;

        for(auto p : played){
            if(p.second == 0) ansA.push_back(p.first);
            if(p.second == 1) ansB.push_back(p.first);
        }

        sort(ansA.begin(), ansA.end());
        sort(ansB.begin(), ansB.end());

        return {ansA, ansB};
    }
};