// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
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
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n-1), b(n-1), x(n-1);
    for (int i=0;i<n-1;i++) {
        cin >> a[i] >> b[i] >> x[i];
        x[i]--;
    }
    dbg(a, b, x);
    /*
    Dijkstra để tính đường đi ngắn nhất từ 1->n
    */
    vector<vector<pair<int,int>>> adj(n);
    for (int i=0;i<n-1;i++) {
        adj[i].push_back({i+1, a[i]});
        adj[i].push_back({x[i], b[i]});
    }
    auto dist = dijkstra(adj, 0);
    cout << dist[n-1];
    show_exec_time();
}

