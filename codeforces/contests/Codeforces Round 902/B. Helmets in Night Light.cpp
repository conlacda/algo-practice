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

struct Human {
    int slot, cost; // số lượng chia sẻ được và cost chia sẻ
    friend bool operator<(Human x, Human y) {
        return x.cost > y.cost;
    }
    friend std::ostream& operator<<(std::ostream& os, const Human s) { return os << destructure(s);}
};

void solve() {
    int n, p;
    cin >> n >> p;
    vector<int> canShare(n), cost(n);
    for (auto &v: canShare) cin >> v;
    for (auto &v: cost) cin >> v;
    /*
    Trưởng làng chia sẻ cho 1 người -> priority_queue
    */
    priority_queue<Human> pq, remain;
    pq.push(Human{INF, p}); // trưởng làng
    for (int i=0;i<n;i++) {
        remain.push(Human{canShare[i], cost[i]});
    }
    int ans = 0;
    while (!remain.empty()) {
        auto call = pq.top(); pq.pop();
        auto rm = remain.top(); remain.pop();
        ans += call.cost;
        pq.push(rm);
        call.slot--;
        if (call.slot > 0) pq.push(call);
    }
    cout << ans << '\n';
    dbg(remain);
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
RE:
    binary search - INF ??
*/