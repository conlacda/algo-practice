// https://codeforces.com/contest/1843/problem/D
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
// const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

void solve() {
    int n;
    cin>> n;
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> leafNum(n, 0);
    function<int(int, int)> cal = [&](int u, int p){
        if (adj[u].size() == 1 && adj[u][0] == p) {
            leafNum[u] = 1;
            return leafNum[u]; // leaf
        }
        for (auto v: adj[u]) {
            if (v == p) continue;
            leafNum[u] += cal(v, u); 
        }
        return leafNum[u];
    };
    cal(0, -1);
    dbg(leafNum);
    int q;
    cin >> q;
    for (int i=0;i<q;i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        cout << leafNum[u] * leafNum[v] <<'\n';
    }
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin>> n;
    while (n--) solve();
    
    show_exec_time();
}