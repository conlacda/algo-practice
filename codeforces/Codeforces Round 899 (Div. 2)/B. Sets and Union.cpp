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
    vector<vector<int>> a(n);
    for (int i=0;i<n;i++) {
        int sz; cin >> sz;
        for (int j=0;j<sz;j++) {
            int k; cin >> k;
            a[i].push_back(k);
        }
    }
    // Với 1 số - xóa toàn bộ số đó khỏi set thì có ans là bao nhiêu
    std::function<int(int)> cal = [&](int u){
        unordered_set<int> us;
        for (int i=0;i<n;i++) {
            int contain = false;
            for (auto v: a[i]) {
                if (v == u) contain = true;
            }
            if (!contain) {
                for (auto v: a[i]) us.insert(v);
            }
        }
        return us.size();
    };
    unordered_set<int> all;
    for (auto v: a) {
        for (auto u: v) all.insert(u);
    }
    int ans = 0;
    for (auto v: all) {
        ans = max(ans, cal(v));
    }
    cout << ans << '\n';
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int test_num = 1;
    cin >> test_num;
    while (test_num--) solve();
    
    show_exec_time();
}
