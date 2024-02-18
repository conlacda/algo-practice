// https://atcoder.jp/contests/abc341/tasks/abc341_c
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
    /*
    Bruteforces cho toàn bộ grid
    */
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    vector<string> grid(n);
    for (auto&v: grid) cin >> v;
    std::function<bool(int, int)> isOk = [&](int x, int y) {
        if (grid[x][y] == '#') return false;
        for (auto v: s) {
            if (v == 'L') y--;
            if (v == 'R') y++;
            if (v == 'U') x--;
            if (v == 'D') x++;
            if (x <0 || x >= n || y < 0 || y >= m || grid[x][y] == '#') return false;
        }
        return true;
    };
    int ans = 0;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (isOk(i, j)) {
                ans++;
            }
        }
    }
    cout << ans;
    show_exec_time();
}
