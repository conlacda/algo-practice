// [Atcoder|Codeforces].abcxxx.F
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
    string t;
    cin >> t;
    int ts = t.size();
    int n;
    cin >> n;
    // dp[index][length] = money
    vector<vector<int>> dp(n, vector<int>(ts, INF/2));
    for (int i=0;i<n;i++) {
        int k;
        cin >> k;
        while (k--) {
            string s;
            cin >> s;
            if (i == 0) {
                if (s == t.substr(0, s.size())) dp[i][(int) s.size() -1] = 1;
            }
            else {
                dbg(s);
                for (int j=0;j<(int) t.size();j++) {
                    dp[i][j] = min(dp[i][j], dp[i-1][j]);
                    if (s == t.substr(j, (int) s.size())) {
                        if (j == 0) dp[i][(int) s.size() -1] = 1;
                        else
                        dp[i][j+(int)s.size() -1] = min(dp[i][j+(int)s.size() -1], dp[i-1][j-1]+1);
                    }
                }
            }
        }
    }
    if (dp[n-1][ts-1] >= INF/2) cout << -1;
    else cout << dp[n-1][ts-1];
    show_exec_time();
}
/*
for (int j=0;j<(int) t.size();j++) {
                if (j > 0 && dp[j-1] == INF/2) continue;
                if (s == t.substr(j, (int) s.size())) {
                    if (j == 0) dp[j+(int) s.size() -1] = 1;
                    else
                        dp[j+(int) s.size() -1] = min(dp[j-1] + 1, dp[j+(int) s.size() -1]);
                }
            }
*/
