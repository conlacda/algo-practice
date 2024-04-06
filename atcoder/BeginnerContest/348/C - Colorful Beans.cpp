// https://atcoder.jp/contests/abc348/tasks/abc348_c
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
    map<int, int> m;
    for (int i=0;i<n;i++) {
        int a, b;
        cin >> a >> b;
        if (m.count(b) == 0) {
            m[b] = a;
        } else {
            m[b] = min(m[b], a);
        }
    }
    int ans = 0;
    for (auto v: m) {
        ans = max(ans, v.second);
    }
    cout << ans;
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
