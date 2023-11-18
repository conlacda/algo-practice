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
    Duyệt mọi số k mà n chia hết rồi tính tổng -> dùng prefix sum
    In ra kết quả
    */
    vector<int> pref(n);
    int cur=  0;
    for (int i=0;i<n;i++) {
        cur += a[i];
        pref[i] = cur;
    }
    std::function<int(int, int)> sum = [&](int u, int v){
        if (u == 0) return pref.at(v);
        return pref.at(v) - pref.at(u-1);
    };
    std::function<int(int)> maxForK = [&](int k){
        int res = 0;
        for (int i=0;i<n/k;i++) {
            res = max(res, sum(i*k, (i+1)*k-1));
        }
        return res;
    };
    std::function<int(int)> minForK = [&](int k){
        int res = INF;
        for (int i=0;i<n/k;i++) {
            res = min(res, sum(i*k, (i+1)*k-1));
        }
        return res;
    };
    int ans = 0;
    for (int k=1;k<=sqrt(n);k++) {
        if (n % k !=0) continue;
        int kk = n / k;
        ans = max(ans, maxForK(k) - minForK(k));
        if (kk != n)
            ans = max(ans, maxForK(kk) - minForK(kk));
    }
    cout << ans<<'\n';
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