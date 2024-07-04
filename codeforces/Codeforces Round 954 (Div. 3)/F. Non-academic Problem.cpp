// https://codeforces.com/problemset/problem/1986/F
// F. Non-academic Problem - 1900
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

class DSU {
 public:
    vector<int> parent, size;
    int n;
    DSU(int _n) {
        n = _n;
        size.resize(n, 1);
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);   
    }

    int find(int v) {
        assert(0 <= v && v < n);
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
    bool isSame(int a, int b) {
        return find(a) == find(b);
    }
};

set<pair<int,int>> findBridges(vector<vector<int>>& adj) {
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
    // sort(bridges.begin(), bridges.end());
    return set(bridges.begin(), bridges.end());
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // Lấy ra cut edges
    // Rồi từ cut edge tính số lượng node bên trái + số lượng node bên phải của 
    // đồ thị
    auto bridges = findBridges(g);
    if (bridges.size() == 0) {
        cout << n * (n-1) /2 << '\n';
        return;
    }
    // Bỏ toàn bộ bridge edge đi thì sẽ lấy được 1 tree
    // việc duyệt tree lấy ra các khối là xong
    DSU dsu(n);
    for (int i=0;i<n;i++) {
        for (auto v: g[i]) {
            if (bridges.find({min(i, v), max(i, v)}) == bridges.end()) {
                dsu.merge(i, v);
            }
        }
    }
    dbg(bridges);
    // Dựng lên tree mình cần
    vector<set<int>> tree(n);
    for (int i=0;i<n;i++) {
        for (auto v: g[i]) {
            if (!dsu.isSame(i, v)) {
                auto ri = dsu.find(i);
                auto rv = dsu.find(v);
                tree[ri].insert(rv);
                tree[rv].insert(ri);
            }
        }
    }
    auto r = dsu.find(0);
    vector<int> points(n, -1);
    std::function<int(int, int)> cal = [&](int u, int p) {
        points[u] = dsu.size[u];
        for (auto v: tree[u]) {
            if (v != p) {
                points[u] += cal(v, u);
            }
        }
        return points[u];
    };
    cal(r, r);
    int ans = n * (n-1) / 2;
    for (int i=0;i<n;i++) {
        if (points[i] != -1) {
            int after = points[i] * (points[i]-1)/2 +  (n - points[i] -1 ) * (n - points[i])/2;
            ans = min(ans, after);
        }
    }
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    while (n--) {
        solve();
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
