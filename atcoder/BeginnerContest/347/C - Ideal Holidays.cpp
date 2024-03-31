// https://atcoder.jp/contests/abc347/tasks/abc347_c
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
#define show_exec_time()
#define destructure(a) #a
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> v(n);
    for (auto&u: v) cin >> u;
    set<int> s;
    for (auto u: v) s.insert(u % (a+b));
    vector<int> d;
    for (auto v: s) d.push_back(v);
    dbg(d);
    int w = 0;
    for (int i=1;i<(int) d.size();i++) {
        w = max(w, d[i] - d[i-1] - 1);
    }
    w = max(w, a+b-1-d[(int) d.size() -1] + d[0]);
    dbg(w);
    if (w >= b) cout << "Yes";
    else cout << "No";
    show_exec_time();
}
