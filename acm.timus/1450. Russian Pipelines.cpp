// https://timus.online/problem.aspx?space=1&num=1450
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

struct Edge {
    int from, to, weight;
};
vector<int> bellmanFord(vector<vector<pair<int, int>>> adj, int source) {
    int n = (int) adj.size();
    // Lấy ra danh sách các cạnh
    vector<Edge> edges;
    for (int i=0;i<n;i++) {
        for (auto vw: adj[i]) {
            edges.push_back({i, vw.first, vw.second});
        }
    }
    // Tính dist[]
    vector<int> dist(n, -INF); dist[source] = 0;
    for (int _=0;_<n;_++) {
        // Phần core tương tự như dijkstra
        for (auto edge: edges) {
            if (dist[edge.from] == -INF) continue;
            if (dist[edge.from] + edge.weight > dist[edge.to]) {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }
    return dist;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<vector<pair<int,int>>> adj(n);
    for (int i=0;i<q;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;v--;
        adj[u].push_back({v, w});
    }
    int source, sink;
    cin >> source >> sink;
    source--; sink--;
    auto dist = bellmanFord(adj, source);
    if (dist[sink] == -INF) cout << "No solution";
    else  cout << dist[sink];
    show_exec_time();
}
/*
Bellman-ford truyền thống tính đường đi ngắn nhất.
Tại đây sửa 1 chút phần core để tính đường đi dài nhất
*/
