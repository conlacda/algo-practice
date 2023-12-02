#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    vector<int> color(n);
    for (auto &v: color) cin >> v;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> ans(n, 0);
    /*
    Dùng reference chứ đừng dùng dạng thông thường rồi return.
    Khi đó set<> được copy sẽ TLE
    */
    std::function<void(set<int>&, set<int>)> merge = [&](set<int>& a, set<int>b){
        if ((int) a.size() < (int) b.size()) swap(a, b);
        for (auto &v: b) a.insert(v);
    };
    std::function<set<int>(int, int)> cal = [&](int u, int p){
        set<int> discolor;
        discolor.insert(color[u]);
        for (auto v: adj[u]) {
            if (v == p) continue;
            merge(discolor, cal(v, u));
        }
        ans[u] = discolor.size();
        return discolor;
    };
    cal(0, -1);
    for (auto v: ans) cout <<v << " ";
    
    show_exec_time();
}