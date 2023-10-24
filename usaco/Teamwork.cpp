// http://www.usaco.org/index.php?page=viewproblem2&cpid=863
// USACO 2018 December Contest, Gold
// Problem 3. Teamwork
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    // #ifdef DEBUG
        freopen("teamwork.in", "r", stdin);
        freopen("teamwork.out", "w", stdout);
    // #endif
    cout << std::fixed << setprecision(15);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    // Push dp dp[index]
    // Khởi tạo
    vector<int> dp(n, 0);
    // transition
    for (int i=0;i<n;i++) {
        int cur = a[i];
        for (int j=0;j<k;j++) {
            if (i+j<n) {
                cur = max(cur, a[i+j]);
                if (i == 0) {
                    dp[i+j] = cur * (j+1);
                } else
                dp[i+j] = max(dp[i+j], dp[i-1] + cur * (j+1));
            }
        }
    }
    dbg(dp);
    // answer
    cout << dp[n-1];    
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