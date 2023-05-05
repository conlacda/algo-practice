// https://cses.fi/problemset/task/1695/
// https://cses.fi/problemset/result/6007247/
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
    vector<vector<ll>> graph(n, vector<ll> (n, 0));
    for (int i=0;i<q;i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        graph[u][v] += 1;
        graph[v][u] += 1;
    }
    dbg(graph);
    Dinic_Maxflow dinic(graph);
    auto mc = dinic.normal_mincut(0, n-1);
    cout << mc.size() <<'\n';
    for (auto v: mc) {
        cout << v.first+1 << ' '<< v.second+1<< '\n';
    }
    show_exec_time();
}
    
