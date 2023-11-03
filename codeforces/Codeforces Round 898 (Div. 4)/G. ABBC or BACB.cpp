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

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}

void solve() {
    string s;
    cin >> s;
    dbg(s);
    // Dem so phan A va bo di phan nho nhat
    if (std::count(s.begin(), s.end(), 'B') == 0) {
        cout << 0 << '\n';
        return;
    }
    vector<int> a;
    int cur = 0;
    for (auto v: s) {
        if (v == 'A') {
            cur++;
        } else {
            a.push_back(cur);
            cur = 0;
        }
    }
    if (cur != 0) a.push_back(cur);
    sort(a.begin(), a.end());
    dbg(a);
    if (s[0] != 'B' && s[(int) s.size() - 1] != 'B') {
        cout << reduce(a.begin(), a.end()) - a[0] << '\n';
    } else 
        cout << reduce(a.begin(), a.end())<< '\n';
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
*/