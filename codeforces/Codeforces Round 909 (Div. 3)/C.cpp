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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    dbg(a);
    /*
    Giải thường trước
    Duyệt tới khi gặp chẵn lẻ giống nhau thì đứt đoạn
    */
    vector<int> dp(n);
    int cur = 0;
    for (int i=0;i<n;i++) {
        if (cur < 0) cur = 0;
        cur = cur + a[i];
        if (cur > 0 && (a[i] - a[i-1]) % 2 == 0) {
            cur = a[i];
        }
        dp[i] = cur;
    }
    cout << *max_element(dp.begin(), dp.end()) << '\n';
    dbg(dp);
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
    int vs long long
RE:
    binary search - INF ??

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
*/