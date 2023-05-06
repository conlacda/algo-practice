// https://cses.fi/problemset/task/1709/
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i=0;i<n;i++) cin >> a[i];
    // Tạo ra đồ thị dạng bipartite
    ll node_num = 2+ 2*n;
    vector<vector<ll>> graph(node_num, vector<ll>(node_num, 0));
    int source = 0, sink = 1;
    for (int i=0;i<n;i++) graph[source][2+i] = 1;
    for (int i=0;i<n;i++) graph[2+n+i][sink] = 1;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (a[i][j] == 'o') graph[2+i][2+n+j] = 1;
        }
    }
    Dinic_Maxflow dinic(graph);
    cout << dinic.max_flow(source, sink) <<'\n';
    dinic.cal_minimum_cover_node();
    for (auto v: dinic.minimum_cover_col){
        cout << 2<< ' ' << v+1<<'\n';
    }
    for (auto v: dinic.minimum_cover_row) {
        cout << 1<<' '<< v+1 <<'\n';
    }
    show_exec_time();

}
