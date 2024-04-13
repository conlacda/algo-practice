// https://codeforces.com/contest/1092/problem/F
#include<bits/stdc++.h>

typedef long long ll; // double long double
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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto dist = dijkstra(adj);
    /*
    Use rerooting technique
    * Calculate subtree from root
    * Move from u->v
    Subtree contain the sum of subtree
    */
    int sum = 0;
    for (auto v: a) sum += v;
    // Calculate for root
    vector<int> ans(n, 0);
    for (int i=0;i<n;i++)
        ans[0] += a[i] * dist[i];
    // Calculate subtree
    vector<int> subtree(n);
    std::function<int(int, int)> calSubtree = [&](int u, int p) {
        subtree[u] = a[u];
        for (auto&v: adj[u]) {
            if (v == p) continue;
            subtree[u] += calSubtree(v, u); // ***
        }
        return subtree[u];
    };
    calSubtree(0, -1);
    // Move from u -> v
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v: adj[u]) {
            if (v == p) continue;
            // ***
            ans[v] = ans[u];
            ans[v] -= subtree[v];
            ans[v] += sum - subtree[v];
            dfs(v, u);
        }
    };
    dfs(0, -1);
    cout << *max_element(ans.begin(), ans.end());
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
