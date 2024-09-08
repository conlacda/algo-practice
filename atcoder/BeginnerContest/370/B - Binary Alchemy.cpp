// https://atcoder.jp/contests/abc370/tasks/abc370_b
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
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i=0;i<n;i++) {
        for (int j=0;j<i+1;j++) {
            cin >> a[i][j];
            a[i][j]--;
        }
    }
    int ans = 0;
    for (int i=0;i<n;i++) {
        dbg(ans, i);
        if (ans >= i) {
            ans = a[ans][i];
        } else ans = a[i][ans];
        dbg(ans);
    }
    cout << ans + 1;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Đọc chậm rãi
Viết ra ý tưởng
Tìm pattern
*/
