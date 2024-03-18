// [Atcoder|Codeforces].abcxxx.F
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
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    dbg(a);
    // Duyệt qua lấy ra tổng lớn nhất
    if (c > 0) {
        int cur = 0;
        int m = 0;
        for (int i=0;i<n;i++) {
            cur += a[i];
            if (cur < 0) cur = 0;
            else m = max(m, cur);
        }
        int sum = 0;
        for (auto&v: a) sum += v;
        if (m > 0) sum += (c-1) * m;
        cout << sum;
    } else {
        int cur = 0;
        int m = 0;
        // tìm ra dãy có tổng âm nhất
        for (auto v: a) {
            cur += v;
            if (cur > 0) cur = 0;
            else m = min(m, cur);
        }
        int sum = 0;
        for (auto&v: a) sum += v;
        dbg(sum, m);
        if (c == 0) cout << sum - m;
        else
        cout << sum + c * m -m;
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
*/
