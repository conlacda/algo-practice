// [Atcoder|Codeforces].abcxxx.F
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
    int n;
    cin >> n;
    vector<int> q(n), a(n), b(n);
    for (auto& v: q) cin >> v;
    for (auto& v: a) cin >> v;
    for (auto& v: b) cin >> v;
    /*
    Thử toàn bộ x từ 0->1e6 rồi tìm ra xem y là bao nhiêu
    từ đó tính được max(x + y)
    */
    std::function<int(int)> cal = [&](int x) {
        int y = INF;
        for (int i=0;i<n;i++) {
            if (x * a[i] > q[i]) return -INF;
            if (b[i] != 0) {
                y = min(y, (q[i] - x * a[i]) / b[i]);
            }
        }
        return y;
    };
    int ans = 0;
    for (int i=0;i<=1e6;i++) {
        ans = max(ans, i + cal(i));
    }
    cout << ans;
    show_exec_time();
}
