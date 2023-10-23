// https://codeforces.com/contest/1883/problem/A
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
    string s;
    cin >> s;
    string sample = "1234567890";
    int ans = 0;
    int cur_index = 0;
    for (auto v: s) {
        int digit = v - '0';
        if (digit == 0) digit = 10;
        int cur_digit = sample[cur_index] - '0';
        if (cur_digit == 0) cur_digit = 10;
        ans += abs(cur_digit - digit);
        ans++;
        dbg(cur_digit, digit, ans);
        cur_index = digit-1;
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