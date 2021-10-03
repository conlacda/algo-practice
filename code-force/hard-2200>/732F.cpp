/*
Thuật toán: 
Tại đây dễ nhận thấy đề bài yêu cầu tìm ra các scc nếu bỏ đi các bridge
Scc nào lớn nhất là giá trị cần tìm
Từ đó sẽ dfs() ra các thành phần khác và đó cũng chính là chiều cần tìm
Dùng map<pair<int,int>, bool> grid để đánh dấu true false cho các cạnh
https://codeforces.com/contest/732/submission/130725887
*/
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

bool cmp(vector<int> a, vector<int> b){
    return a[a.size()-1] < b[b.size()-1];
}

class Graph{ // graph chung cho tất cả
public:
    // General part
    int V; // vertex num 0->V-1
    vector<vector<pair<int,int>>> G;
    vector<bool> visited;
    Graph(int V){
        this->V  = V +1;
        G.resize(this->V, {});
        visited.resize(this->V, false);
    }
    void addEdge(int u, int v, int w = -1){
        G.at(u).push_back({v, w});
    }
    // Verification: https://www.spoj.com/problems/EC_P/
    // Reference: https://cp-algorithms.com/graph/bridge-searching.html
    vector<int> pre, low;
    int clock = 0;
    vector<pair<int,int>> bridges;
    vector<int> parent;
    void explore_for_bridge_searching(int u){
        visited[u] = true;
        pre[u] = low[u] = clock++;
        for (int i=0;i<G[u].size();i++){
            int v = G[u][i].first;
            if (v == parent[u]) continue; // u duyệt tới v thì bỏ qua v duyệt tới u
            if (visited[v]) {
                low[u] = min(low[u], pre[v]);
            } else {
                parent[v] = u;
                explore_for_bridge_searching(v);
                low[u] = min(low[u], low[v]);
                if (low[v] > pre[u]) // nghĩa là u đi thẳng tới v. v ko chạm tới điểm nào đằng trước u
                    // nếu v->x mà x->u thì low[v] = pre[x] <= pre[v] (= khi x là v). khi này u,v,x thuộc 1 đường tròn 
                    // IS_BRIDGE(u, to);
                    bridges.push_back({u, v});
            }
        }
    }
    
    void findBridges(){
        visited.assign(V, false);
        parent.assign(V, -1);
        pre.assign(V, -1); low.assign(V, -1);
        for (int i = 0; i < V; ++i) { // DFS()
            if (!visited[i])
                explore_for_bridge_searching(i);
        }
    }
    vector<vector<int>> scc;
    set<int> bridge_nodes;
    vector<bool> vis;
    // vector<vector<bool>> grid;
    map<pair<int,int>, bool> grid;
    vector<int> buff;
    void explore(int u){
        if (!vis[u]){
            buff.push_back(u);
            vis[u] = true;
            for (int i=0;i<G[u].size();i++){
                int v = G[u][i].first;
                // if (!grid[u][v] && !vis[v]) {
                // m.find("f") == m.end() 
                if (grid.find({u, v}) == grid.end() && !vis[v]){
                    explore(v);
                }
            }
        }
    }
    vector<vector<int>> ans;
    void expl(int u){
        if (!vis[u]){
            vis[u] = true;
            for (int i=0;i<G[u].size();i++){
                int v = G[u][i].first;
                // if (!grid[u][v] && !grid[v][u])
                if (grid.find({u, v}) == grid.end() && grid.find({v, u}) == grid.end())
                    ans.push_back({v, u, G[u][i].second});
                // grid[u][v] = true;
                grid[{u, v}] = true;
                if (!vis[v]) {
                    expl(v);
                }
            }
        }
    }
    void solve(){
        // Initial
        vis.resize(V, false);
        grid.clear();
        for (int i=0;i<bridges.size();i++){
            grid[{bridges[i].second, bridges[i].first}] = true;
            grid[{bridges[i].first, bridges[i].second}] = true;

        }
        // get bridge node
        for (auto v: bridges){
            bridge_nodes.insert(v.first);
            bridge_nodes.insert(v.second);
        }
        // Get scc
        for (int i=1;i<V;i++){
            buff.clear();
            explore(i);
            if (buff.size() !=0) scc.push_back(buff);
        }
        int max_size_scc = 0 , start_node;
        for (auto v: scc) {
            if (v.size() > max_size_scc) {
                max_size_scc = v.size();
                start_node = v[0];
            }
        }
        cout << max_size_scc << "\n";
        vis.assign(V, false);
        grid.clear();
        expl(start_node);
        sort(ans.begin(), ans.end(), cmp);
        for (auto v: ans) {
            cout << v[0] << ' ' << v[1] << '\n';
        }
    } 
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, M;
    cin >> N >> M;
    Graph g(N);
    for (int i=0;i<M;i++){
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v, i);
        g.addEdge(v, u, i);
    }
    g.findBridges();
    // Tim SCC sau khi break cac bridge
    g.solve();
}
