// [Atcoder|Codeforces].abcxxx.F
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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    int m;
    cin >> m;
    vector<int> b(m);
    for (auto&v: b) cin >> v;
    int l;
    cin >> l;
    vector<int> c(l);
    for (auto&v: c) cin >> v;
    set<int> sum;
    for (auto&v: a)
        for (auto&v1: b)
            for (auto&v2: c)
                sum.insert(v+v1+v2);
    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        if (sum.find(x) != sum.end()) {
            cout << "Yes\n";
        } else cout << "No\n";
    }

    show_exec_time();
}
