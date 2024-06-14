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
    /*
    Với 1 tọa độ x, y tìm ra màu của nó
    */
    std::function<int(int, int, int)> color = [&](int x, int y, int k) {
        if (k == 0) return (int) 1;
        int sq = (int) pow(3, k-1);
        int row = x/sq;
        int col = y/sq;
        if (col == 1 && row == 1) return (int) 0;
        return color(x%sq, y%sq, k-1);
    };
    for (int i=0;i<(int) pow(3, n);i++) {
        for (int j=0;j<(int) pow(3, n);j++) {
            if (color(i, j, n)) {
                cout << "#";
            } else cout << ".";
        }
        cout << '\n';
    }

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
