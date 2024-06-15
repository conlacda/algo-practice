// [Atcoder|Codeforces].abcxxx.F
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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto&v: a) cin >> v;
    for (auto&v: b) cin >> v;
    /*
    Sắp xếp
    */
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i=0,j=0;
    int ans = 0;
    while (i < n && j < m) {
        while (a[i] < b[j]) {
            i++;
            if (i >= n) {
                cout << -1;
                return 0;
            }
        }
        ans += a[i];
        i++; j++;
    }
    if (j == m) cout << ans;
    else cout << -1;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
