// https://codeforces.com/contest/1877/problem/D
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

int power(int a, int b, int m = mod) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

struct Element {
    int index, value;
    friend std::ostream& operator<<(std::ostream& os, const Element s) { return os << destructure(s);}
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    /*
    Tính max cho từng index -> sắp xếp dãy với value + index
    -> duyệt từng số rồi tách thành prime -> cập nhật max index
    ncr để tính số lần xuất hiện của từng index
    */
    int n;
    cin >> n;
    vector<Element> a(n);
    for (int i=0;i<n;i++) {
        int x; cin >> x;
        a[i] = Element{i+1, x};
    }
    vector<int> _max(n, 0);
    for (auto v: a) {
        // index, value
        for (int i=1;i*i<=v.index;i++) {
            if (v.index % i == 0) {
                _max[i-1] = max(_max[i-1], v.value);
                _max[v.index / i -1] = max(_max[v.index/i-1], v.value);
            }
        }
    }
    int ans = 0;
    sort(_max.rbegin(), _max.rend());
    for (int i=0;i<n;i++) {
        ans %= mod;
        ans += power(2, n-i-1) * _max.at(i);
        ans %= mod;
    }
    cout << ans;
    show_exec_time();
}
