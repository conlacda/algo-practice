// https://cses.fi/problemset/task/1195/
#include<bits/stdc++.h>
 
typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
 
using namespace std;
 
#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif
 
<dijkstra>

struct Edge {
    int u, v;
    ll w;
};
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, e;
    cin >> n >> e;
    vector<vector<pair<int, ll>>> adj(n), radj(n);
    vector<Edge> edges;
    for (int i=0;i<e;i++) {
        int u, v, w;
        cin >> u >> v>> w;
        u--;v--;
        adj[u].push_back({v, w});
        radj[v].push_back({u, w});
        edges.push_back({u, v, w});
    }
    auto to = dijkstra(adj, 0);
    auto back = dijkstra(radj, n-1);
    /*
    Sửa lại dijkstra - thêm root vào, đầu vào là đồ thị, đầu ra là khoảng cách
    khoảng cách root tới root luôn bằng 0
    viết 2 hàm 1 hàm dijkstra cho có trọng số, 1 cái có trọng số mặc định là 1.
    thêm template vào cho nó
    thêm reverseGraph vào template
    */
    // dbg(to, back);
    ll ans = LLONG_MAX;
    for (auto edge: edges) {
        int u = edge.u, v = edge.v;
        if (to[u] != -1 && back[v] != -1)
            ans = min(ans, to[u] + back[v] + edge.w/2);
    }
    cout << ans;
    show_exec_time();
}
