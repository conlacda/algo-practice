// https://atcoder.jp/contests/abc361/tasks/abc361_e
// [Atcoder|Codeforces].abcxxx.F
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

int diameter(vector<vector<pair<int,int>>> adj) { // vector<vector<pair<int, int>>> adj
    vector<ll> dist = dijkstra(adj);
    int f1 = std::distance(dist.begin(), max_element(dist.begin(), dist.end()));
    dist = dijkstra(adj, f1);
    int f2 = std::distance(dist.begin(), max_element(dist.begin(), dist.end()));
    return dist[f2];
    // return make_pair(f1, f2);
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
    vector<vector<pair<int,int>>> g(n);
    int ans = 0;
    for (int i=0;i<n-1;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        ans += w * 2;
    }
    // Lấy toàn bộ tổng các đường trừ đi đường kính
    cout << ans - diameter(g);

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Bài này đơn giản chỉ là nếu nó đi từ 1 điểm và quay lại thì độ dài đường đi là 2 * tổng toàn bộ cạnh của đồ thị
Nhưng nếu ko phải quay lại thì sẽ tiết kiệm được 1 đoạn đường đi về.
Chọn đoạn đường đi về đó là dimeter thì kết quả cuối sẽ là 2 * sum(all edges) - diameter
*/