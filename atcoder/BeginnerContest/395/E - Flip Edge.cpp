#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

struct X {
    int cost;
    bool flip = false;
};

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<int>> graph(n), rgraph(n);
    for (int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        rgraph[v].push_back(u);
    }
    vector<pair<int,int>> cost(n, {INF, INF});
    cost[0].first = 0;
    queue<X> Q;
    Q.push(X{0, false});
    while (!Q.empty()) {
        auto [u, flip] = Q.front();
        Q.pop();
        if (!flip) {
            for (auto&v: graph[u]) {
                if (cost[v].first > cost[u].first + 1) {
                    cost[v].first = cost[u].first + 1;
                    Q.push({v, flip});
                }
            }
            if (cost[u].second > cost[u].first + x) {
                cost[u].second = cost[u].first + x;
                Q.push({u, !flip});
            }
        } else {
            for (auto&v: rgraph[u]) {
                if (cost[v].second > cost[u].second + 1) {
                    cost[v].second = cost[u].second + 1;
                    Q.push({v, flip});
                }
            }
            if (cost[u].first > cost[u].second + x) {
                cost[u].first = cost[u].second + x;
                Q.push({u, !flip});
            }
        }
    }
    dbg(cost);
    cout << min(cost[n-1].first, cost[n-1].second);

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
