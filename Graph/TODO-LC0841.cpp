class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int len = rooms.size();
        vector<bool> vis(len, false);

        vis[0] = true;

        queue<int> q;
        for(auto el : rooms[0]) q.push(el);

        while(!q.empty()){
            int key = q.front();
            q.pop();
            vis[key] = true;

            for(int el : rooms[key]){
                if(!vis[el]) q.push(el);
            }
        }

        for(auto el : vis) if(!el) return false;
        return true;
    }
};
