#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

//friend std::ostream& operator<<(std::ostream& os, const S &s) { return os << destructure(s);}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i=0;i<n;i++) cin >> a[i];
    vector<int> ans(k+1, 0);
    // Khởi tạo dp
    for (auto v: a) if (v <= k) ans[v] = 1;
    // Tính dp
    for (int i=0;i<=k;i++) {
        for (auto coin: a) {
            if (i-coin >=0) ans[i] += ans[i - coin]; // hàm quan trọng nhất
            ans[i] %= mod;
        }
    }
    cout << ans[k];
}
/*
dp[k] = tổng các dp[k-coin].
Coin Combinations I
https://cses.fi/problemset/task/1635/
*/
