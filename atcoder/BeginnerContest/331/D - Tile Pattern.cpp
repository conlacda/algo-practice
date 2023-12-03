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
    int n, q;
    cin >> n >> q;
    vector<string> g(n);
    for (auto &v: g) cin >> v;
    // 1 query tinh mat N
    // Dung prefix_sum de tinh
    // vector<vector<int>> pref(n, vector<int>(n));
    // Tinh prefix sum cho phan 2D -> hinh nay se bi tach thanh 9 phan khac nhau
    vector<vector<int>> pref(n, vector<int>(n, 0)), row(n, vector<int>(n, 0));
    for (int i=0;i<n;i++) {
        int s = 0;
        for (int j=0;j<n;j++) {
            if (g[i][j] == 'B') s++;
            row[i][j] = s;
        }
    }
    for (int c=0;c<n;c++) {
        int s = 0;
        for (int r=0;r<n;r++) {
            s += row[r][c];
            pref[r][c] = s;
        }
    }
    std::function<int(int, int, int, int)> cal = [&](int a, int b, int c, int d){
        // assert(c >= a && d >= b);
        if (c <a  || d < b) return (int) 0;
        if (a == 0 && b == 0) return pref[c][d];
        if (a == 0) return pref[c][d] - pref[c][b-1];
        if (b == 0) return pref[c][d] - pref[a-1][d];
        return pref[c][d] + pref[a-1][b-1] - pref[c][b-1] - pref[a-1][d];
    };
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int ans = 0;
        dbg(a, b, c, d);
        int upa = (a/n+1)*n;
        int upb = (b/n+1)*n;
        int downc = c/n*n;
        int downd = d/n*n;
        ans += cal(a%n, b%n, n-1, n-1);
        ans += cal(0, b%n, n-1, n-1) * ((downc - upa) / n);
        ans += cal(0, b%n, c%n, n-1);
        ans += cal(0, 0, c%n, n-1) * ((downd - upb) /n);
        ans += cal(a%n, 0, n-1, n-1) * ((downd - upb) / n);
        ans += cal(0, 0, n-1, n-1) * ((downd - upb) /n) * ((downc - upa) /n);
        ans += cal(a%n, 0, n-1, d%n);
        ans += cal(0, 0, n-1, d%n) * ((downc - upa) /n);
        ans += cal(0, 0, c%n, d%n);
        cout << ans << '\n';
    }
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
        // if (a <= upa-1 || b <= upb-1)

        ans += cal(a%n, b%n, n-1, n-1); // goc trai
        ans += cal(0, b, n-1, n-1) * ((downc - upa)/n); // ma trai
        ans += cal(0, b, c, n-1);

*/