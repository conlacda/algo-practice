// https://atcoder.jp/contests/abc323/tasks/abc323_d
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

struct Slime {
    int sz, sl;
    friend bool operator<(Slime a, Slime b) {
        return a.sz > b.sz;
    }
    friend std::ostream& operator<<(std::ostream& os, const Slime s) { return os << destructure(s);}
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
    priority_queue<Slime> pq;
    for (int i=0;i<n;i++) {
        int u, v;
        cin >> u >> v;
        pq.push(Slime{u, v});
    }
    dbg(pq);
    int ans = 0;
    while (pq.size() > 1) {
        auto top = pq.top(); pq.pop();
        auto next = pq.top();
        if (top.sz == next.sz) {
            pq.pop();
            next = Slime{top.sz, top.sl + next.sl};
            pq.push(next);
            continue;
        }
        // int times = log(top.sz, next.sz);
        int times = ceil(log2((double) next.sz / top.sz));
        int so_cuc_1 = pow(2, times);
        int remain = top.sl % so_cuc_1;
        int new_sl = (top.sl - remain) / so_cuc_1;
        int new_size = top.sz * so_cuc_1;
        ans += std::popcount((unsigned int) remain);
        if (new_sl != 0) {
            pq.push(Slime{new_size, new_sl});
        }
    }
    ans += std::popcount((unsigned int)pq.top().sl);
    cout << ans;
    /*
    Sắp xếp slime theo kích thước
    Tổng hợp slime nhỏ tới to
    Tổng hợp slime thứ 1 to hơn slime thứ 2 và pop()
    rồi push vào priority_queue
    Cuối cùng là in kết quả
    */
    dbg(log2(10));
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