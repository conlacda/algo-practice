#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

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
vector<ll> dijkstra(vector<vector<pair<int, ll>>> adj, int root = 0){
    int n = (int) adj.size();
    vector<bool> visited(n, false);
    priority_queue<Node> Q;
    vector<ll> dist(n, LLONG_MAX);
    dist[root] = 0; visited[root] = true;

    for (int i=0;i< (int) adj[root].size();i++){
        int u = adj[root][i].first; ll start_to_u = adj[root][i].second;
        if (dist[u] > start_to_u)
            dist[u] = start_to_u;
        visited[u] = true;
        Q.push({u, dist[u]});
    }

    while (!Q.empty()){
        ll d = Q.top().dist;
        int u = Q.top().id;
        Q.pop();
        if (d > dist[u]) continue;
        for (int i=0;i< (int) adj[u].size();i++){
            ll w = adj[u][i].second; int v = adj[u][i].first;
            if (d+ w < dist[v]){
                dist[v] = d + w;
                Q.push({v, dist[v]});
            }
        }
    }
    // Nếu !hasEdge(start, i) thì dist[i] = -1
    for (int i=0;i< n;i++) if (dist[i] == LLONG_MAX) dist[i] =-1;
    return dist;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    /*
    Đường đi ngắn nhất?? dijkstra
    dijkstra 2 chiều ngược xuôi -> điểm ở giữa chính là điểm switch - cses    
    */
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    vector<vector<int>> v(n, std::vector<int>(n));
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cin >> v[i][j];
        }
    }
    dbg(v);
    vector<vector<pair<int,int>>> adj_car(n);
    vector<vector<pair<int,int>>> adj_train(n);
    for (int i=0;i<n-1;i++) {
        for (int j=i+1;j<n;j++) {
            adj_car[i].push_back({j, v[i][j] * a});
            adj_car[j].push_back({i, v[j][i] * a});
            adj_train[i].push_back({j, v[i][j] * b + c});
            adj_train[j].push_back({i, v[j][i] * b + c});
        }
    }
    auto dist_car = dijkstra(adj_car);
    auto dist_train = dijkstra(adj_train, n-1);
    int ans = INF;
    for (int i=0;i<n;i++) {
        ans = min(ans, dist_car[i] + dist_train[i]);
    }
    cout << ans;
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
*/