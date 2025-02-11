#pragma GCC optimize("O3")
#pragma optimize("Ofast,unroll-loops")
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
    int n;
    cin >> n;
    /*
    Gom toàn bộ các giá trị lại vào nhau
    Tìm ra max
    */
    vector<int> sz(n);
    vector<map<int, int>> a(n);
    for (int i=0;i<n;i++) {
        int k;
        cin >> k;
        sz[i] = k;
        for (int j=0;j<k;j++) {
            int x;
            cin >> x;
            a[i][x]++;
        }
    }
    double ans = 0;
    std::function<void(int, int)> cal = [&](int i, int j) {
        double res = 0;
        for (auto&[k, v]: a[i]) {
            if (a[j].find(k) != a[j].end()) {
                res += v * a[j][k];
            }
        }
        ans = max(ans, res / (sz[i] * sz[j]));
    };
    for (int i=0;i<n-1;i++) {
        for (int j=i+1;j<n;j++) {
            cal(i, j);
        }
    }
    cout << ans;


    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
