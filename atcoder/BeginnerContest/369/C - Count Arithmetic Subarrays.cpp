// https://atcoder.jp/contests/abc369/tasks/abc369_c
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
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    int ans = 0;
    ans += n;
    /*
    Co dinh i roi tim ra j
    */
    int i=0, j=1;
    while (i<n&&j<n) {
        int cur = a[j]-a[i];
        while (j+1<n && a[j+1] - a[j] == cur) {
            j++;
        }
        ans += (j-i+1)*(j-i)/2;
        i=j;
        j++;
    }
    cout << ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
