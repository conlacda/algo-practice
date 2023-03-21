// https://atcoder.jp/contests/abc294/tasks/abc294_g
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
#endif

<HLD-template>
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n;
    cin >> n;
    vector<pair<ll, ll>> edges;
    vector<vector<ll>> adj(n);
    vector<vector<pair<ll, ll>>> adj_w(n);
    for (ll i=0;i<n-1;i++) {
        ll u, v, w;
        cin>> u >> v >> w;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
        adj_w[u].push_back({v, w});
        adj_w[v].push_back({u, w});
    }
    ABCDE<ll> hld(adj);
    vector<ll> height = hld.depth;
    vector<ll> weight(n, -1);
    for (ll i=0;i<(ll) adj_w.size();i++){
        for (auto vw: adj_w[i]){
            ll v = vw.first, w = vw.second;
            if (height[i] > height[v]) weight[i] = w;
            else weight[v] = w;
        }
    }
    hld.bst(weight);
    ll q; cin >> q;
    for (ll i=0;i<q;i++) {
        ll t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            pair<ll, ll> e = edges[u-1];
            ll e1 = e.first;
            ll e2 = e.second;
            hld.svfe(e1, e2, v);
        } else {
            u --; v--;
            cout << hld.qa(u, v)<< '\n';
        }
    }
    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
