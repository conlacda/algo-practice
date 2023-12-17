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
    => max
    Xet tung diem b -> (a+prefa) max la bao nhieu
                    -> (c - lc) max la bao nhieu
    */
    int ans = 0;
    vector<int> pref_plus(n), pref_minus(n);
    for (int i=0;i<n;i++) {
        pref_plus[i] = a[i] + i;
        pref_minus[i] = a[i] - i;
    }
    dbg(pref_plus, pref_minus);
    vector<int> pref_max(n);
    int cur = 0;
    for (int i=0;i<n;i++) {
        cur = max(cur, pref_plus[i]);
        pref_max[i] = cur;
    }
    vector<int> suf_max(n);
    cur = -INF;
    for (int i=n-1;i>=0;i--) {
        cur = max(cur, pref_minus[i]);
        suf_max[i] = cur;
    }
    for (int i=1;i<n-1;i++) {
        ans = max(ans, pref_max[i-1] + a[i] + suf_max[i+1]);
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
