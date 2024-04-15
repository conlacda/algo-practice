// https://atcoder.jp/contests/abc349/tasks/abc349_b
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
    string s;
    cin >> s;
    map<char, int> m;
    for (auto v: s) m[v]++;
    map<int, int> mm;
    for (auto [v, t]: m) {
        mm[t]++;
    }
    for (auto v: mm) {
        if (v.second != 2) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
