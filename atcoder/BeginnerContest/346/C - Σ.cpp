// https://atcoder.jp/contests/abc346/tasks/abc346_c
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    set<int> s(a.begin(), a.end());
    int sum = 0;
    for (auto v: s) {
        if (v > k) break;
        sum += v;
    }
    cout << (1+k)*k/2 - sum;
    show_exec_time();
}
