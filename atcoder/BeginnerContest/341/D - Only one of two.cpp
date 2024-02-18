// https://atcoder.jp/contests/abc341/tasks/abc341_d
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

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
    int n, m, k;
    cin >> n >> m >> k;
    /*
    dùng binary search để tính
    đếm xem số k có bao nhiêu số từ 1->k mà chia hết cho 1 trong 2 số n,m
    */
    std::function<int(int)> cal = [&](int x) {
        int xn = x / n;
        int xm = x / m;
        int xnm = x / lcm(m, n);
        return xn + xm - 2* xnm;
    };
    dbg(cal(8));
    int l = 1, r = INF/2;
    while (l < r) {
        int mid = (l + r) /2;
        if (cal(mid) >= k) {
            r = mid;
        } else l = mid + 1;
    }
    cout << l;
    show_exec_time();
}
