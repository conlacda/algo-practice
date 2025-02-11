// #pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
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

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto&v: a) cin >> v;
    for (auto&v: b) cin >> v;
    map<int, int> m1, m2;
    for (int i=0;i<n;i++) {
        m1[b[i]] = a[i];
    }
    for (int i=0;i<n;i++) {
        m2[i+1] = b[i];
    }
    for (int i=0;i<n;i++) {
        cout << m2[m1[i+1]] << ' ';
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Đọc chậm rãi
Viết ra ý tưởng
*/
