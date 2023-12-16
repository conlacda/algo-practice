// https://codeforces.com/contest/1826/problem/D
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& v: a) cin >> v;
    /*
    a + b + c - (lc - la)
    = a + la + b + c - lc
    = (a + la) + b + (c + sufc) - N
    => max
    Xet tung diem b -> (a+prefa) max la bao nhieu
                    -> (c+prefc) max la bao nhieu
    */
    int ans = 0;
    vector<int> pref(n), suf(n);
    for (int i=0;i<n;i++) {
        pref[i] = a[i] + i;
        suf[i] = a[i] + (n-1) - i;
    }
    vector<int> max_pref(n), max_suf(n);
    int cur = 0;
    for (int i=0;i<n;i++) {
        cur = max(pref[i], cur);
        max_pref[i] = cur;
    }
    cur = 0;
    for (int i=n-1;i>=0;i--) {
        cur = max(suf[i], cur);
        max_suf[i] = cur;
    }
    for (int i=1;i<n-1;i++) {
        ans = max(ans, max_pref[i-1] + a[i] + max_suf[i+1] - n + 1);
    }
    cout << ans <<"\n";
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) {
        solve();
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
