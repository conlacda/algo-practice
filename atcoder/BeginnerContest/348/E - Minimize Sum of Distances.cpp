// https://atcoder.jp/contests/abc348/tasks/abc348_e
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

struct Node {
    int id; ll dist;
    friend bool operator<(const Node &a, const Node &b){
        return a.dist > b.dist;
    }
};
vector<ll> dijkstra(vector<vector<pair<int, ll>>>& adj, int root = 0) {
    int n = (int) adj.size();
    priority_queue<Node> Q;
    vector<ll> dist(n, INF); // LLONG_MAX
    dist[root] = 0;
    
    // Thêm các neighbor của root vào queue
    for (auto uw: adj[root]) {
        int u = uw.first; ll root_to_u = uw.second;
        // Có dòng này bởi vì có thể có nhiều cạnh từ u->v
        if (dist[u] > root_to_u) dist[u] = root_to_u;
        Q.push({u, dist[u]});
    }

    // Mở rộng dần từ các điểm đã có ra
    while (!Q.empty()) {
        ll d = Q.top().dist;
        int u = Q.top().id;
        Q.pop();
        if (d > dist[u]) continue;
        for (auto vw: adj[u]) {
            ll w = vw.second; int v = vw.first;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                Q.push({v, dist[v]});
            }
        }
    }
    // Nếu !hasEdge(start, i) thì dist[i] = -1
    for (int i=0;i< n;i++)
        if (dist[i] == INF) dist[i] =-1;
    return dist;
}

// dijkstra cho adj không có trọng số -> mặc định là 1
vector<ll> dijkstra(vector<vector<int>>& adj, int root = 0) {
    int n = (int) adj.size();
    const int defaultw = 1;
    vector<vector<pair<int, ll>>> ans(n);
    for (int i=0;i<n;i++) {
        for (auto v: adj[i]) {
            ans[i].push_back({v, defaultw});
        }
    }
    return dijkstra(ans, root);
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    mỗi node sẽ có 1 trọng số.
    Khi đi từ u->v thì 1 vài cụm sẽ được tăng lên 1 lượng
    ngược lại cụm gần v sẽ giảm đi 1 lượng
    tính lượng thay đổi của từng edge rồi duyệt dfs() là xong
    -> tính subtree của từng node 1
    */
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> c(n);
    for (auto&v: c) cin >> v;
    dbg(c);
    vector<int> subtree(n, 0);
    std::function<int(int, int)> calSubTree = [&](int u, int p) {
        subtree[u] = c[u];
        for (auto v: adj[u]) {
            if (v == p) continue;
            subtree[u] += calSubTree(v,u);
        }
        return subtree[u];
    };
    calSubTree(0, 0);
    int sumC = 0;
    for (auto v: c) sumC += v;
    // Tính giá trị cho thời điểm ban đầu
    int cur = 0;
    auto distance = dijkstra(adj);
    for (int i=0;i<n;i++) {
        cur += distance[i] * c[i];
    }
    vector<int> f(n, 0);
    f[0] = cur;
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v: adj[u]) {
            int res = f[u];
            if (v == p) continue;
            // res = res + c[u];
            res = res - c[v];
            int sub = subtree[v] - c[v];
            res -= sub;
            res += sumC - subtree[v];
            f[v] = res;
            dfs(v, u);
        }
    };
    dfs(0, 0);
    cout << *min_element(f.begin(), f.end());
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Bài này cho mỗi đỉnh 1 số ci
Tại 1 node u, lấy sum dist(u, v) * cv
Rồi hỏi node u nào cho tổng nhỏ nhất.
Xét 2 node u, v kề nhau.
Giả sử tính được sum(dist(u, i) * ci) sẵn cho đỉnh u rồi
Từ đỉnh u ta cần tính được cho v -> chỉ cần duyệt dfs() là tính được cho mọi đỉnh
Ta thấy từ u->v thì mọi đỉnh của subtree(v) sẽ gần thêm và sum sẽ trừ đi 1 lượng bằng sum(ci với i là các node của subtree)
sum sẽ được tăng thêm 1 cho mọi đỉnh nằm ở hướng ngược lại được tính bằng sum(c.begin() - c.end()) - sum(ci với i thuộc subtree(v))
-> ta tính trước sum(c.begin(), c.end())
-> tính trước sumC(subtree) cho mọi node bằng dfs()
-> tính sum(dist * c) cho điểm khởi đầu
-> dfs chuyển từ u->v là tính được mọi f(i) với i = 0..n-1
-> lấy min(f.begin(), f.end()) là xong
*/
