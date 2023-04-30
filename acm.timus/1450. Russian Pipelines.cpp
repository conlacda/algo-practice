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
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    // cout << std::fixed << setprecision(2);
    int n, q;
    cin >> n >> q;
    vector<vector<pair<int,int>>> adj(n);
    vector<Edge> edges;
    for (int i=0;i<q;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;v--;
        adj[u].push_back({v, w});
        edges.push_back(Edge{u, v, w});
    }
    int source, sink;
    cin >> source >> sink;
    source--; sink--;
    std::function<vector<int>(int source)> bellmanford = [&](int source){
        vector<int> dist(n, -INF); dist[source] = 0;
        for (int _=0;_<n-1;_++) {
            for (auto edge: edges) {
                if (dist[edge.from] == -INF) continue;
                if (dist[edge.from] + edge.weight > dist[edge.to]) {
                    dist[edge.to] = dist[edge.from] + edge.weight;
                }
            }
        }
        return dist;
    };
    auto dist = bellmanford(source);
    if (dist[sink] == -INF) cout << "No solution";
    else  cout << dist[sink];
    dbg(dist);
    show_exec_time();
}
// Using the Bellman-ford algorithm
