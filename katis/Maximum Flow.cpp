// https://open.kattis.com/problems/maxflow
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

<dinic-max-flow>

struct Edge{
    ll u, v, w;
};
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    // cout << setprecision(2);
    int n, e, source, sink;
    cin >> n >> e>> source>> sink;
    vector<Edge> edges;
    vector<vector<ll>> graph(n, vector<ll>(n, 0));
    for (int i=0;i<e;i++){
        ll u, v, w;
        cin >> u >> v>> w;
        edges.push_back({u, v, w});
        graph[u][v] = w;
    }
    Dinic_Maxflow dinic(graph);
    dbg(dinic.max_flow(source, sink));
    cout << n << ' '<< dinic.max_flow(source, sink) <<' ';
    vector<Edge> ans;
    for (Edge eg: edges){
        if (dinic.residualGraph[eg.u][eg.v] < eg.w){
            ans.push_back({eg.u, eg.v, eg.w - dinic.residualGraph[eg.u][eg.v]});
        }
    }
    cout << ans.size() <<'\n';
    for (auto v: ans){
        cout << v.u << ' '<< v.v<< ' '<< v.w<<'\n';
    }
    show_exec_time();
}
