// https://codeforces.com/contest/1883/problem/B
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
    string s;
    cin >> s;
    map<char, int> m;
    for (auto v: s) {
        m[v]++;
    }
    for (auto& v: m) {
        if (k == 0) break;
        if (v.second % 2 == 1) {
            k--;
            v.second--;
        }
    }
    // Nếu mà k hết -> check xem có 2 số lẻ nào đồng thời xảy ra ko
    if (k == 0) {
        int cnt = 0;
        for (auto v: m) {
            if (v.second %2 == 1) cnt++;
        }
        if (cnt > 1) {
            cout << "No\n";
            return;
        } else {
            cout << "Yes\n";
            return;
        }
    }
    cout << "Yes\n";
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