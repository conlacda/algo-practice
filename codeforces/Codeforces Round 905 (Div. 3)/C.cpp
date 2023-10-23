// https://codeforces.com/contest/1883/problem/C
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    int ans = k;
    if (k == 4) {
        // Chia cho 4 hoặc 2 số chia cho 2
        int even =0;
        for (auto v: a) {
            dbg(v);
            if (v  % 4 == 0) {
                ans = 0;
                break;
            }
            if (v % 2 == 0) {
                even++;
                if (even >= 2) {
                    ans = 0;
                    break;
                }
            }
            if (v % 4 == 3) {
                ans = min(ans, (int) 1);
            }
            if (even != 0) ans = min(ans, (int) 1);
        }
        dbg(even);
        ans = min(ans, (int) 2);
    } else {
        for (auto v: a) {
            int r = v %k;
            if (r == 0) {
                ans = 0;
                break;
            }
            if (r > 0) ans = min(ans, k-r);
        }
    }
    
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    while (n--) solve();
    
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
*/