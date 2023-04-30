//https://www.spoj.com/problems/QTREE2/
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


<HLD with>
    static H merge(H a, H b){
        return a + b;
    }
    static const H null_val = 0;
    static const bool weight_on_edge = true;

void solve(){
    int N;
    cin >> N;
    vector<vector<int>> adj(N);
    vector<vector<pair<int,ll>>> adj_w(N);
    for (int i=0;i<N-1;i++){
        int u, v, w;
        cin >> u>>v>>w;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        adj_w[u].push_back({v, w});
        adj_w[v].push_back({u, w});
    }
    HeavyLightDecomposition<int> hld(adj);
    vector<int> weight(N, -1);
    for (int i=0;i<adj_w.size();i++){
        for (auto vw: adj_w[i]){
            int v = vw.first, w = vw.second;
            if (hld.depth[i] > hld.depth[v]) weight[i] = w;
            else weight[v] = w;
        }
    }
    hld.buildSegTree(weight);
    while (true){
        string s; 
        cin >>s;
        if (s == "DIST"){
            int u, v; 
            cin>>u>>v; u--;v--;
            int p = hld.lca.lca(u, v);
            cout << hld.query(u, p) + hld.query(v, p)<<'\n';
        } else if(s == "KTH"){
            int u, v, k; cin >> u>>v>>k; u--;v--;k--;
            int p = hld.lca.lca(u, v);
            int up = hld.depth[u] - hld.depth[p];
            if (k<=up){
                cout << hld.kth_ancestor(u, k) +1<<'\n';
            } else {
                int vk = hld.depth[u] + hld.depth[v] - 2*hld.depth[p] - k;
                cout << hld.kth_ancestor(v, vk) +1 <<'\n';
            }
        } else {
            break;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N;
    cin >> N;
    while (N--) solve();
}
