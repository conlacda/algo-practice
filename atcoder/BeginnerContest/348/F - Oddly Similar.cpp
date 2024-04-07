// https://atcoder.jp/contests/abc348/tasks/abc348_f
#pragma GCC optimize("Ofast,unroll-loops") // O3
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
    vector<vector<int>> a(n, vector<int>(m));
    for (auto&row: a) {
        for (auto&v: row)
            cin >> v;
    }
    std::function<bool(int, int)> isSimilar = [&](int i, int j) {
        int cnt = 0;
        for (int k=0;k<m;k++) {
            if (a[i][k] == a[j][k]) {
                cnt++;
            }
        }
        if (cnt % 2 == 1) return true;
        return false;
    };
    int res = 0;
    for (int i=0;i<n-1;i++) {
        for (int j=i+1;j<n;j++) {
            if (isSimilar(i, j)) res++;
        }
    }
    dbg(res);
    cout << res;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
*/
