// https://codeforces.com/contest/1324/problem/F
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> c(n);
    for (auto&v: c) {
        cin >> v;
        if (v == 0) v = -1;
    }
    dbg(c);
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    /*
    Tính giá trị max cho subtree
    Node 1 mk giá trị 0 thì là -1, node 1 thì là 1
    có 10 node -> 9 node trắng, 1 node đen -> 9-1=8=10-2*1 = sum - 2 * black
    */
    vector<int> subtree(n);
    std::function<int(int, int)> calSubtree = [&](int u, int p) {
        // subtree[u] = 1 - 2 * c[u];
        subtree[u] = c[u];
        for (auto&v: adj[u]) {
            if (v == p) continue;
            subtree[u] += max(calSubtree(v, u), (int) 0);
        }
        return subtree[u];
    };
    calSubtree(0, 0);
    dbg(subtree);
    // rerooting tại đây
    vector<int> ans(n);
    ans[0] = subtree[0];
    std::function<void(int, int)> dfs = [&](int u, int p) {
        // lấy thêm các phần từ node cha
        for (auto v: adj[u]) {
            if (v == p) continue;
            /*
            u->v
            u đã tính được rồi
            nếu đoạn ans[u] có count cả v thì là ans[v] = ans[u] -> chỉ cần subtree[v] >= 0 là được
            ngược lại thì nó bằng chính nó
            */
            if (subtree[v] >= 0) {
                // có kết nối nếu mà ans[u] cũng dương
                if (ans[u] >= subtree[v]) {
                    ans[v] = ans[u];
                } else {
                    ans[v] = subtree[v];
                }
            } else {
                // âm thì chỉ có 1 node v được giữ lại
                assert(subtree[v] == -1);
                ans[v] = max(subtree[v], ans[u] + subtree[v]);
            }
            dfs(v, u);
        }
    };
    dfs(0, -1);
    for (auto&v: ans) cout << v << ' ';
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}