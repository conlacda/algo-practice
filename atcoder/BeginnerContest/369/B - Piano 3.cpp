// https://atcoder.jp/contests/abc369/tasks/abc369_b
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
    int n;
    cin >> n;
    int ans = 0;
    int l = -1, r = -1;
    while (n--) {
        int k;
        char lr;
        cin >> k >> lr;
        if (lr == 'L') {
            if (l != -1) ans += abs(l-k);
            l=k;
        } else {
            if (r != -1) ans += abs(r-k);
            r=k;
        }
    }
    cout << ans;


    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
