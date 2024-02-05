// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

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
    int row, col, n;
    cin >> row >> col >> n;
    vector<string> ans(row, string(col, '.'));
    vector<pair<int,int>> drs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int drIndex = 0;
    int x = 0, y =0;
    for (int i=0;i<n;i++) {
        if (ans[x][y] == '.') {
            ans[x][y] = '#';
            drIndex++;
            if (drIndex > 3) drIndex = 0;
        } else {
            ans[x][y] = '.';
            drIndex--;
            if (drIndex <0) drIndex = 3;
        }
        x += drs[drIndex].first; if (x >= row) x = 0; if (x <0) x = row-1;
        y += drs[drIndex].second; if (y >= col) y = 0; if (y < 0) y = col-1;
    }
    for (auto v: ans) cout << v << '\n';
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
