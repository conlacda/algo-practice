// https://atcoder.jp/contests/abc361/tasks/abc361_c
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
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
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    sort(a.begin(), a.end());
    dbg(a);
    if (n - k == 1) {
        cout << 0;
        return 0;
    }
    int ans = INF/2;
    // Xóa đi k số -> còn lại n-k số
    int remain = n - k;
    for (int i=0;i<n;i++) {
        if (i + remain - 1 < n) {
            dbg(i + remain -1, i, a[i + remain -1] - a[i]);
            ans = min(ans, a[i + remain -1] - a[i]);
        }
    }
    cout << ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
