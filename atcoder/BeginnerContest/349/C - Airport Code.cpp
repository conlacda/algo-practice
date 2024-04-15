// https://atcoder.jp/contests/abc349/tasks/abc349_c
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
    string t, s;
    cin >> t >> s;
    for (auto &v: s) v = tolower(v);
    if (s[(int) s.size() - 1] == 'x') s = s.substr(0, (int) s.size() -1);
    dbg(t, s);
    int p = 0;
    int n = t.size();
    for (int i=0;i<n;i++) {
        if (t[i] == s[p]) {
            p++;
            if (p == (int) s.size()) {
                cout << "Yes";
                return 0;
            }
        }
    }
    cout << "No";


    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
