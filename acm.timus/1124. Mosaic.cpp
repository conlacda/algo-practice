#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

// Full doc: https://github.com/conlacda/docc/blob/dev/docs/competitive-programming/graph/basic/toposort.md
vector<vector<int>> findSCC(vector<vector<int>> G){
    // Tạo ra reversed graph
    std::function<vector<vector<int>>(vector<vector<int>>)> getReversedGraph = [&](vector<vector<int>> G){
        vector<vector<int>> rG((int) G.size());
        for (int i=0;i<G.size();i++){
            for (auto v: G[i]){
                rG[v].push_back(i);
            }
        }
        return rG;
    };
    // Topo order
    std::function<vector<int>(vector<vector<int>>)> toposort = [&](vector<vector<int>>G){
        vector<bool> vis(G.size(), false);
        vector<int> order;
        std::function<void(int)> dfs = [&](int u){
            if (!vis[u]) {
                vis[u] = true;
                for (auto v: G[u]){
                    if (!vis[v]) dfs(v);
                }
                order.push_back(u);
            }
        };
        for (int i=0;i<(int) G.size();i++) {
            dfs(i);
        }

        reverse(order.begin(), order.end());
        return order;
    };

    vector<int> post_orders_reversed_graph = toposort(getReversedGraph(G)); // topo sort on reversed graph
    vector<vector<int>> result;
    std::vector<bool> vis((int) G.size(), false);
    vector<int> scc;
    std::function<void(int)> dfs = [&](int u){
        vis[u] = true;
        for (auto v: G[u]){
            if (!vis[v]){
                dfs(v);
            }
        }
        scc.push_back(u);
    };
    for (auto i: post_orders_reversed_graph){
        if (!vis[i]) dfs(i);
        if (scc.size() > 0){
            result.push_back(scc);
            scc = {};
        }
    }
    reverse(result.begin(), result.end());
    return result;
}
/*  findSCC(vector<vector<int>> graph);
    result = {{3, 0}, {4, 1}, {5}, {2}}
*/
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    /*
    Có M hộp màu, mỗi hộp có N mảnh.
    Mỗi hộp màu đang bị sai màu - Chỉnh lại số màu có trong đó với thao tác ít nhất
    Đặt tay vào 1 hộp x, đưa tay từ hộp x sang hộp y (có thể di chuyển/ko di chuyển gì mất 1 thao tác)
    Có bao nhiêu thao tác cần thực hiện để làm các hộp màu về bình thường
    => Các màu đã đúng thì ko cần xét tới
    => Dựng 1 đồ thị 
    => Kết quả sẽ bằng tổng các cạnh + tổng số SCC-1
    */
    int m, n;
    cin >> m >> n;
    vector<vector<int>> a(m, std::vector<int>(n));
    vector<unordered_map<int, int>> _map(m);
    int ans = 0;
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) {
            cin >> a[i][j];
            a[i][j]--;
            if (a[i][j] != i) {
                _map[i][a[i][j]]++;
                ans++;
                dbg(i, ans);
            }
        }
    }
    dbg(_map);
    // Tu do thi tinh so scc
    vector<vector<int>> adj(m);
    for (int i=0;i<m;i++) {
        for (auto p: _map[i]) {
            adj[i].push_back(p.first);
        }
    }
    auto scc = findSCC(adj);
    auto non_empty_scc = 0;
    for (auto v: scc) {
        if (v.size() > 1) {
            non_empty_scc++;
        }
    }
    cout << ans + max(non_empty_scc -1, 0);    
    show_exec_time();
}
