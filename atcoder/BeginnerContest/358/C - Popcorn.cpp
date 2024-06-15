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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i=0;i<n;i++) {
        string x;
        cin >> x;
        int num = 0;
        for (int j=0;j<k;j++) {
            if (x[j] == 'o') {
                num += 1 << (k - j -1);
            }
        }
        a[i] = num;
    }
    int ans = INF/2;
    for (int i=0;i<(1<<n);i++) {
        int cnt = 0;
        int num = 0;
        for (int j=0;j<n;j++) {
            if (i & (1 << j)) {
                cnt++;
                num = num | a[j];
            }
        }
        dbg(cnt, num);
        if (num == (1<<k) - 1) {
            ans = min(ans, cnt);
        }
    }
    dbg((1<<(k+1)) - 1);
    cout << ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
