// Atcoder.abcxxx.F
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n,k;
    cin >> n >> k;
    vector<int> a(k);
    for (auto& v: a) cin >> v;
    n = (int) a.size();
    // int l = 0, r =0;
    // for (int i=0;i<(int) a.size();i+=2) {
    //     if (i+1<(int) a.size()) {
    //         l += a[i+1] - a[i];
    //     }
    // }
    // for (int i=(int)a.size()-1;i>=0;i-=2) {
    //     if (i-1>=0)
    //         r += a[i] - a[i-1];
    // }
    // dbg(a);
    // dbg(l, r);
    // cout << min(l, r);
        dbg(a);
    if (k % 2==0) {
        int ans = 0;
        for (int i=0;i<n;i+=2) {
            ans += a[i + 1] - a[i];
        }
        cout << ans;
        return 0;
    }
    vector<int> l, r;
    int cur =0;
    for (int i=0;i<n;i+=2) {
        if (i+1<n) {
            cur += a[i+1] - a[i];
            l.push_back(cur);
        }
    }
    cur = 0;
    for (int i=n-1;i>=0;i-=2) {
        if (i-1>=0) {
            cur += a[i] - a[i-1];
            r.push_back(cur);
        }
    }
    int ans = INF;
    for (int i=0;i<n;i+=2) {
        int ll = 0;
        if (i != 0) ll = l[i/2-1];
        int rr = 0;
        if (i +1 < n) rr = r[(n-i) /2-1];
        ans = min(ans, ll + rr);
    }
    cout << ans;
    dbg(l, r);
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
Neu ma chan thi tru di nhau la xong
Le thi phai bo di 1 so
*/
