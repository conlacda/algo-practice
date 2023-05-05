// https://cses.fi/problemset/task/1694/
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
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<vector<int>> graph(n, vector<int> (n, 0));
    for (int i=0;i<q;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;v--;
        graph[u][v] += w;
    }
    Dinic_Maxflow dinic(graph);
    cout << dinic.max_flow(0, n-1);
    
    show_exec_time();
}
