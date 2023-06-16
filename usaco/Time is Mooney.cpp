#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1e9 + 7; // 998244353  1000000009  1000000007
#define ld long double

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
    #else
        freopen("time.in", "r", stdin);
        freopen("time.out", "w", stdout);
    #endif
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> a(n);
    for (int i=0;i<n;i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n);
    for (int i=0;i<m;i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
    }
    /*
    Từ điểm 0 đi quanh đồ thị rồi trở về thì tổng max là bao nhiêu
    Có thể đi nhiều vòng
    ans = max(0, sum - c*t^2)
    c là hằng số
    max_sum = t*max_m = 1000 * t
    sum - c*t^2 >= 0 => 1000*t > t^2 => 1000 >= t.
    Tức là chỉ nên di chuyển tối đa 1000 ngày
    Dùng dp[t][node] - đánh dấu node và ngày tới node đó
    */
    // Initial state
    vector<vector<int>> dp(1001, vector<int>(n, -1));
    dp[0][0] = 0;
    // Transition dp[t][v] = dp[t-1][u] + a[v] với u->v
    for (int t=1;t<1001;t++) {
        for (int u=0;u<n;u++) {
            if (dp[t-1][u] == -1) continue;
            for (auto v: adj[u]) {
                dp[t][v] = max(dp[t][v] ,dp[t-1][u] + a[v]);
            }
        }
    }
    // Get answer
    int ans = 0;
    for (int t=1;t<1001;t++) {
        ans = max(ans, dp[t][0] - c*t*t);
    }
    cout << ans;
    show_exec_time();
}
