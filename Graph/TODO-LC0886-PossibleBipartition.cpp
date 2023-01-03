class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        vector<int> vis(n+1, -1);

        vector<vector<int>> graph(n+1, vector<int>({}));
        for(auto el : dislikes){
            graph[el[0]].push_back(el[1]);
            graph[el[1]].push_back(el[0]);
        }

        queue<pair<int,int>> q;

        for(int i = 1; i <= n; ++i){
            if(vis[i] != -1) continue;

            q.push({i, 0});

            while(!q.empty()){
                auto [person, group] = q.front();
                q.pop();
                vis[person] = group;

                for(auto el : graph[person]){
                    if(vis[el] == -1){
                        if(group == 0) q.push({el, 1});
                        else q.push({el, 0});
                    }
                    else if(vis[el] == group) return false;
                }
            }
        }
        return true;
    }
};
