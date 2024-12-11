// https://atcoder.jp/contests/dp/tasks/dp_o
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007;
#define int long long // __int128
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
    /*
    dp[{set of woman}][cur_index]
    */
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto&v: a)
        for (auto&u: v) cin >> u;

    vector<vector<int>> dp(1 << n, vector<int>(n, 0));
    // Init
    for (int i=0;i<n;i++) {
        if (a[0][i] == 1)
            dp[1 << i][0] = 1; // dp[woman_mask][last_index]
    }
    // Trans
    auto getbit = [](int bit, int i) -> int { return (bit >> i) & 1; };
    auto turnon = [](int bit, int i) -> int { return bit | (1 << i); };
    for (int mask=1; mask < (1 << n); mask++) {
        for (int man=1;man<n;man++) {
            for (int woman=0;woman<n;woman++) {
                if (dp[mask][man-1] != 0 && a[man][woman] == 1 && !getbit(mask, woman)) {
                    dp[turnon(mask, woman)][man] += dp[mask][man - 1];
                    dp[turnon(mask, woman)][man] %= mod;
                }
            }
        }
    }
    // Ans
    cout << dp[(1<<n) - 1][n-1];

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
