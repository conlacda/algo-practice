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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int k;
    cin >> k;
    int n = 1414214;
    vector<int> a(n);
    for (int i=0;i<n;i++) {
        a[i] = i*i;
    }
    int ans = INF;
    for (int i=0;i<n;i++) {
        int r = abs(k - a[i]);
        // Tim so kep giua remain la xong
        auto up = upper_bound(a.begin(), a.end(), r);
        if (up != a.end()) {
            int val = *up;
            if (a[i] >= k) {
                ans = min(ans, r + val);
            } else
                ans = min(ans, abs(r - val));
        }
        if (up != a.begin()) {
            auto low = prev(up);
            if (a[i] >= k) {
                ans = min(ans, abs(r + *low));
            } else
                ans = min(ans, abs(r - *low));
        }
    }
    cout << ans;
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