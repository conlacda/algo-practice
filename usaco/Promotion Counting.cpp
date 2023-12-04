#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
    #else
        freopen("promote.in", "r", stdin);
        freopen("promote.out", "w", stdout);
    #endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    vector<vector<int>> adj(n);
    for (int i=1;i<n;i++) {
        int p;
        cin >> p;
        p--;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    vector<int> ans(n, 0);
    std::function<ordered_set<int>(int, int)> cal = [&](int u, int p){
        // set<int> res;
        ordered_set<int> res;
        for (auto v: adj[u]) {
            if (v == p) continue;
            auto resV = cal(v, u);
            if ((int) res.size() < (int) resV.size()) {
                res.swap(resV);
            }
            for (auto v: resV) res.insert(v);
            ans[u] = (int) res.size() - res.order_of_key(a[u]);
            // auto upper = res.upper_bound(a[u]);
            // ans[u] = (int) res.size() - std::distance(res.begin(), upper);
        }
        res.insert(a[u]);
        return res;
    };
    cal(0, 0);
    for (auto v: ans) cout << v << '\n';

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
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
