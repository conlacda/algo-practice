// https://codeforces.com/contest/600/problem/E
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
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> ans(n, 0);
    vector<map<int, int>> point(n); // frequence -> sum point
    std::function<map<int, int>(int, int)> cal = [&](int u, int p){
        map<int, int> res; // màu -> số lần xuất hiện
        res[color.at(u)]++;
        point[u][1] = color[u];
        for (auto v: adj[u]) {
            if (v == p) continue;
            auto calU = cal(v, u);
            if ((int) res.size() < (int) calU.size()) {
                res.swap(calU);
                point[u].swap(point[v]);
            }
            for (auto v: calU) {
                int cur_frequence = res[v.first];
                point[u][cur_frequence] -= v.first;
                int new_frequence = res[v.first] + v.second;
                res[v.first] = new_frequence; // màu v.first có thêm v.second lần xuất hiện
                point[u][new_frequence] += v.first;
            }
        }
        ans[u] = point[u].rbegin()->second;
        return res;
    };
    cal(0, -1);
    for (auto v: ans) cout << v << ' ';
    show_exec_time();
}
