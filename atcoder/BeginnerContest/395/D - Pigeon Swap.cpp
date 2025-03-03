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
    /*
    Có 3 thao tác:
    * chuyển ổ của p sang nest
    * swap nest
    * in ra ổ của p
    */
    int n, q;
    cin >> n >> q;
    map<int, int> p2nest;
    for (int i=1;i<=n;i++) p2nest[i] = i;
    map<int, int> nest2nest, rnest2nest;
    for (int i=1;i<=n;i++) {
        nest2nest[i] = i;
        rnest2nest[i] = i;
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, _nest;
            cin >> p >> _nest;
            p2nest[p] = rnest2nest[_nest];
            // Chuyển tổ của p sang nest
        } else if (t == 2) {
            int nest1, nest2;
            cin >> nest1 >> nest2;
            // swap 2 tổ
            // a <-> b | 
            int onest1 = rnest2nest[nest1];
            int onest2 = rnest2nest[nest2];
            nest2nest[onest1] = nest2;
            nest2nest[onest2] = nest1;
            rnest2nest[nest1] = onest2;
            rnest2nest[nest2] = onest1;
        } else {
            int p;
            cin >> p;
            cout << nest2nest[p2nest[p]] << '\n';
        }
    }


    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
