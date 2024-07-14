// https://atcoder.jp/contests/abc357/tasks/abc357_e
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Tìm ra điểm cuối của đồ thị -> toposort để lấy ra
    Từ toposort thì có thể lấy reversed graph để duyệt
    Dùng đồ thị ngược để duyệt từ điểm đó về là xong
    -> cần 1 hàm lấy đồ thị ngược
    -> gói 1 SCC thành 1 node và chuyển nó thành 1 cụm -> dùng DSU để thực hiện
    1 cycle tồn tại khi node đó quay vòng chính node đó
    hoặc node đó nằm trong 1 SCC nhiều phần tử
    */
    int n;
    cin >> n;
    vector<bool> in_cycle(n, false);
    vector<int> point(n, 0);
    vector<vector<int>> g(n);
    for (int i=0;i<n;i++) {
        int u;
        cin >> u; u--;
        if (u == i) {
            in_cycle[i] = true;
            point[i] = 1;
        }
        else
            g[u].push_back(i);
    }
    auto scc = findSCC(g);
    for (auto s: scc) {
        if ((int) s.size() > 1) {
            for (auto v: s) {
                in_cycle[v] = true;
                point[v] = (int) s.size();
            }
        }
    }
    std::function<void(int)> dfs = [&](int u) {
        for (auto v: g[u])
            if (!in_cycle[v]) {
                point[v] = point[u] +1;
                dfs(v);
            }
    };
    for (int i=0;i<n;i++) {
        if (in_cycle[i]) dfs(i);
    }
    int ans = 0;
    for (auto v: point) ans += v;
    cout << ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
