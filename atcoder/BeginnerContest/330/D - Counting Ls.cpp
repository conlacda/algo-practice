#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
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

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    vector<string> a(n);
    for (auto &v: a) cin >> v;
    /*
    Xet tung cot 1. lay 2 diem bat ky cua 1 cot roi gan voi 1 diem khac cua hang la ra
    */
    // Dem so diem cua tung hang, cot
    vector<int> col(n, 0), row(n, 0);
    for (int i=0;i<n;i++) {
        int cnt =0;
        for (int j=0;j<n;j++) {
            if (a[i][j] == 'o') cnt++; 
        }
        row[i] = cnt;
        cnt = 0;
        for (int j=0;j<n;j++) {
            if (a[j][i] == 'o') cnt++;
        }
        col[i] = cnt;
    }
    int ans = 0;
    // cu co diem thi row se duoc tinh 1 lan
    for (int r=0;r<n;r++) {
        for (int c=0;c<n;c++) {
            if (a[r][c] == 'o') {
                ans += (col[c] - 1) * (row[r] - 1);
            }
        }
    }
    cout << ans;
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
*/