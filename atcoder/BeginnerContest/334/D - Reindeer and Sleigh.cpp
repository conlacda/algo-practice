// Atcoder.abcxxx.F
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    sort(a.begin(), a.end());
    dbg(a);
    ordered_set<int> pref;
    int cur = 0;
    for (auto v: a) {
        cur += v;
        pref.insert(cur);
    }
    dbg(pref);
    while (q--) {
        int x;
        cin >> x;
        cout << pref.order_of_key(x+1) << '\n';
    }
    
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
