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
    /*
    Tìm ra dãy tăng ở cuối và so sánh phần đầu
    */
    int mi = a[n-1];
    int k = n-1;
    while (k > 0 && a[k] >= a[k-1]) {
        k--;
        mi = min(mi, a[k]);
    }
    if (k == 0) cout << 0 << '\n';
    else {
        int ma = *min_element(a.begin(), a.begin() + k-1);
        if (ma <= mi) {
            cout << -1 << '\n';
        } else cout << k << '\n';
    }

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