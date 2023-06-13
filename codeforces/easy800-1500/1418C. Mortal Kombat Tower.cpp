// https://codeforces.com/contest/1418/problem/C
// C. Mortal Kombat Tower
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
const int INF = std::numeric_limits<int>::max();

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
    cin >> n;
    vector<int> a(n);
    for (int i=0;i<n;i++) cin >> a[i];
    dbg(a);
    // Initial state
    vector<vector<int>> dp(2, vector<int>(n, INF)); // [human][index]
    dp[0][0] = a[0];
    dp[0][1] = a[0] + a[1];
    // Transition
    for (int i=1;i<n;i++) {
        // dp[1][i] = min(dp[0][i-1], dp[0][i-2]); - người thứ 1 chọn 1/2, kết quả sẽ bằng người thứ 0 chọn 1/2 cái trước đó vì người 1 ko khi nào mất phí
        dp[1][i] = dp[0][i-1];
        if (i >=2) dp[1][i] = min(dp[0][i-1], dp[0][i-2]);
        // dp[0][i] = min(dp[1][i-1] + a[i], dp[1][i-2] + a[i] + a[i-1]); - người thứ 0 chọn bằng người thứ nhất chọn 1/2 cái trước đó cộng với a[i]  vì người 0 lúc nào cũng mất phí
        if (i > 1) dp[0][i] = dp[1][i-1] + a[i];
        if (i > 2)  dp[0][i] = min(dp[1][i-1] + a[i], dp[1][i-2] + a[i] + a[i-1]);
    }
    cout << min(dp[0][n-1], dp[1][n-1]) <<'\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    while (n--) solve();
    
    show_exec_time();
}
