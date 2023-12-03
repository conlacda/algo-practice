#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (auto& v: a) cin >> v;
    for (auto&v: b) cin >> v;
    map<int, vector<int>> no;
    for (int i=0;i<k;i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        no[u].push_back(v);
    }
    map<int, int, std::greater<int>> _map;
    for (auto v: b) _map[v]++;
    /*
    Any idea:??
    Voi moi mon o a tim ra mon lon nhat o b ko bi banned trong O(logN)
    */
    int ans = 0;
    for (int i=0;i<n;i++) {
        // Tim ra mon o b
        for (auto j: no[i])
            _map[b[j]]--;

        for (auto v: _map) {
            if (v.second != 0) {
                ans = max(ans, v.first + a[i]);
                break;
            }
        }

        for (auto j: no[i])
            _map[b[j]]++;
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
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/