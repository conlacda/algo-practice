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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    // n >= 1, m >= 0, k >= 1
    if (k > 3) {
        cout << 0 <<"\n";
        return;
    }
    if (k == 1) {
        cout << 1 <<'\n'; // m = 0
        return;
    }
    if (k == 2) {
        // mọi số m nhỏ hơn hoặc bằng n + mọi số chia hết cho n
        // [1->n]
        int ans = min(n, m);
        if (m <= n) {
            cout << ans << '\n';
            return;
        } else {
            ans += m/n-1;
            cout << ans <<'\n';
            return;
        }
    }
    if (k == 3) {
        if (m <= n) {
            cout << 0 <<'\n';
            return;
        }
        // số lượng số > n không chia hết cho n
        // [n+1 -> m]
        int d = m/n - 1;
        cout << (m - n) - d << '\n';
        return;
    }

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