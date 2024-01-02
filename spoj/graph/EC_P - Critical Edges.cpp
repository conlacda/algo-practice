// https://www.spoj.com/problems/EC_P/
#include<bits/stdc++.h>

#define int long long // __int128

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

/*
Trả về danh sách các bridge có trong đồ thị
*/
vector<pair<int,int>> findBridges(vector<vector<int>>& adj) {
    int n = (int) adj.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1), pre(n, -1), low(n, -1);
    int clock = 0;
    vector<pair<int,int>> bridges;
    std::function<void(int)> dfs = [&](int u){
        visited[u] = true;
        pre[u] = low[u] = clock++;
        for (int i=0;i< (int) adj[u].size();i++){
            int v = adj[u][i];
            if (v == parent[u]) continue; // u duyệt tới v thì bỏ qua v duyệt tới u
            if (visited[v]) {
                low[u] = min(low[u], pre[v]);
            } else {
                parent[v] = u;
                dfs(v);
                low[u] = min(low[u], low[v]);
                if (low[v] > pre[u]) // nghĩa là u đi thẳng tới v. v ko chạm tới điểm nào đằng trước u
                    // nếu v->x mà x->u thì low[v] = pre[x] <= pre[v] (= khi x là v). khi này u,v,x thuộc 1 đường tròn 
                    bridges.push_back({min(u, v), max(u, v)}); // (u, v) là được. min, max thêm vào để edge có thứ tự
            }
        }
    };
    for (int i=0;i<n;i++) {
        if (!visited[i]) dfs(i);
    }
    sort(bridges.begin(), bridges.end());
    return bridges;
}

void solve(int tc) {
    cout << "Caso #" << tc << '\n';
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto bridges = findBridges(adj);
    if ((int) bridges.size() == 0) {
        cout << "Sin bloqueos\n";
    } else {
        cout << bridges.size() << '\n';
        for (auto uv: bridges) {
            cout << uv.first +1 << ' '<< uv.second+1 << '\n';
        }
    }
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    for (int i=1;i<=n;i++) solve(i);

    show_exec_time();
}
