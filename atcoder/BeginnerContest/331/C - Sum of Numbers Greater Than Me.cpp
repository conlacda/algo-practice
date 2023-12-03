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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    vector<int> b = a;
    sort(b.begin(), b.end());
    map<int, int> m;
    int s = 0;
    for (auto v: b) s+=v;
    for (int i=0;i<n-1;i++) {
        s -= b[i];
        if (b[i] == b[i+1]) continue;
        m[b[i]] = s;
    }
    m[b[n-1]] = 0;
    for (auto v: a) cout << m[v] << ' ';
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