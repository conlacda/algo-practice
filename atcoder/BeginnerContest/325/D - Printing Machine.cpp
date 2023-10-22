#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
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

struct X {
    int s, e;
    bool friend operator<(X a, X b) {
        return a.e > b.e;
    }
    friend std::ostream& operator<<(std::ostream& os, const X s) { return os << destructure(s);}
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    vector<X> a(n);
    for (int i=0;i<n;i++) {
        int s, t;
        cin >> s >> t;
        a[i] = X{s, s+t};
    }
    sort(a.begin(), a.end(), [&](X u, X v){
        return u.s < v.s;
    });
    dbg(a);
    /*
    Liên tục đẩy cái a vào queue khi nó chưa được xử lý
    */
    priority_queue<X> pq;
    int v = a[0].s;
    int cur = 0;
    int ans = 0;
    while (true) {
        while (v >= a[cur].s && cur < n) {
            pq.push(a[cur]);
            cur++;
        }
        while (!pq.empty() && v > pq.top().e) pq.pop();
        if (cur >= n && pq.empty()) break;
        if (pq.empty()) {
            v = a[cur].s;
            continue;
        }
        dbg(pq.top(), pq);
        pq.pop();
        ans++;
        v++; // TLE
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
RE:
    binary search - INF ??
*/