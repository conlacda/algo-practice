#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

const int mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
    }
    vector<vector<int>> dp(1 << n, vector<int>(n, 0));
    int start = 0, end = n-1;
    dp[1 << start][start] = 1; // 1 cách bắt đầu tại điểm start
    auto getbit = [](int bit, int i) -> int { return bit & (1 << i);};
    auto turnon = [](int bit, int i) -> int { return bit | (1 << i); };
    for (int bit = 1; bit < (1 << n); bit++) {
        for (int i=0;i<n;i++) {
            if (!getbit(bit, i)) continue;
            for (auto&j: g[i]) {
                if (dp[bit][i] == 0) continue; // very important
                if (getbit(bit, j)) continue;
                dp[turnon(bit, j)][j] += dp[bit][i];
                dp[turnon(bit, j)][j] %= mod;
            }
        }
    }
    cout << dp[(1 << n) - 1][end];

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
