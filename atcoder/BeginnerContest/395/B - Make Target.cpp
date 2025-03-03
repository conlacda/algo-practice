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
    int n;
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n, '#'));
    std::function<void(int)> cal = [&](int layer) {
        // hàng ngang
        if (layer % 2 == 0) return;
        for (int i=layer;i<n-layer;i++) {
            grid[layer][i] = '.';
            grid[n-1-layer][i] = '.';
            grid[i][layer] = '.';
            grid[i][n-1-layer] = '.';
        }
    };
    int layer_num = n/2 + 1;
    for (int i=0;i<layer_num;i++) {
        cal(i);
    }
    for (auto&v: grid) {
        for (auto&u: v)
            cout << u;
        cout << '\n';
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
