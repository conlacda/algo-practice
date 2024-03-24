// https://atcoder.jp/contests/abc346/tasks/abc346_d
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

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
    string ss;
    cin >> ss;
    vector<int> s;
    for (auto v: ss) s.push_back(v - '0');
    vector<int> c(n);
    for (auto&v: c) cin >> v;
    dbg(c);
    /*
    DP??
    dp[index][last][good] = cost;
    */
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2, INF/2)));
    // initial
    dp[0][s[0]][0] = 0;
    dp[0][1-s[0]][0] = c[0];
    // transition
    for (int i=1;i<n;i++) {
        dp[i][s[i]][0] = min(dp[i][s[i]][0], dp[i-1][1-s[i]][0]);
        dp[i][s[i]][1] = min(dp[i][s[i]][1], dp[i-1][1-s[i]][1]);
        dp[i][s[i]][1] = min(dp[i][s[i]][1], dp[i-1][s[i]][0]);
        dp[i][1-s[i]][0] = min(dp[i][1-s[i]][0], dp[i-1][s[i]][0] + c[i]);
        dp[i][1-s[i]][1] = min(dp[i][1-s[i]][1], dp[i-1][1-s[i]][0] + c[i]);
        dp[i][1-s[i]][1] = min(dp[i][1-s[i]][1], dp[i-1][s[i]][1] + c[i]);
    }
    // answer dp[n-1][0/1][1]
    cout << min(dp[n-1][0][1], dp[n-1][1][1]);
    show_exec_time();
}

