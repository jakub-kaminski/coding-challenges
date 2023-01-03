class Solution {
public:
    string frequencySort(string s) {
        map<char,int> m;
        for(char c : s) ++m[c];

        vector<pair<int,char>> v;
        for(auto el : m) v.push_back({el.second, el.first});

        sort(v.begin(), v.end());

        string res = "";

        for(int i = v.size()-1; i >= 0; --i){
            for(int k = 0; k < v[i].first; ++k){
                res.push_back(v[i].second);
            }
        }

        return res;
    }
};
