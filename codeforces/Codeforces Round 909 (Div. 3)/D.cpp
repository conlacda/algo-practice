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
    if (n == 1) {
        cout << '0' <<'\n';
        return;
    }
    map<int, int> m;
    sort(a.begin(), a.end());
    dbg(a);
    int ans = 0;
    for (auto v: a) m[v]++;
    a.resize(unique(a.begin(), a.end()) - a.begin());
    for (int i=1;i<(int) a.size();i++) {
        if (a[i] - a[i-1] == 1 && a[i] == a[i-1] * 2) {
            ans += m[a[i]] * m[a[i-1]];
        }
    }
    for (auto v: m) {
        ans += v.second * (v.second-1) /2;
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
    int vs long long
RE:
    binary search - INF ??

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
*/