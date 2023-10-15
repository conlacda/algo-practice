// https://codeforces.com/contest/1832/problem/E
// Difficulty: 2200
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const int mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
// #define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

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
    cout << std::fixed << setprecision(15);
    int n, a0, x, y, m, k;
    cin >> n >> a0 >> x >> y >> m >> k;
    vector<int> a(n);
    a[0] = a0;
    for (int i=1;i<n;i++) {
        a[i] = (1LL * a[i-1] * x + y) % m;
    }
    vector<int> pref;
    int cur = 0;
    for (int i=0;i<n;i++) {
        cur += a[i];
        cur %= mod;
        pref.push_back(cur);
    }
    // Memoization
    vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
    // map<pair<int,int>, int> memo; - dùng map gây ra TLE
    // Dùng unordered_map thì phải thêm hàm hash cho nó
    // Bài này N = 1e7 thay vì 1e6 nên đoạn #define int long long không dùng được mà phải dùng 1LL để tính toán
    std::function<int(int, int)> cal = [&](int i, int k){
        if (memo[i][k] != -1) return memo[i][k];
        if (k == 0) {
            memo[i][k] = pref[i] % mod;
            return pref[i] % mod;
        }
        if (i == 0) {
            memo[i][k] = (int) 0;
            return (int) 0;
        }
        // Công thức: cal(i, k) = cal(i-1, k) + cal(i-1, k-1) - công thức nCr
        // cal(i,k) bản chất là iCk.
        // có đoạn pref kia là phải nghĩ 1 chút mới ra.
        // khi k = 0 thì mọi hệ số đều bằng 1 -> sẽ là tổng từ a[i] trở về a[1]
        // hay chính là prefix_sum[i]
        memo[i][k] = (cal(i-1, k) % mod + cal(i-1, k-1) % mod) % mod;
        return memo[i][k];
    };
    vector<int> b(n);
    for (int i=0;i<n;i++) {
        b[i] = cal(i+1, k);
    }
    // dbg(b);
    ll ans = 0;
    for (int i=0;i<n;i++) {
        ans = ans ^ (1LL* b[i] * (i+1));
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
RE:
    binary search - INF ??
*/
