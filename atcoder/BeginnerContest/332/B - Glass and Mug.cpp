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
    int n, g, m;
    cin >> n >> g >> m;
    int cg = 0, cm = 0;
    std::function<void()> doAction = [&](){
        if (cm == 0) {
            if (cg == g) {
                cg = 0;
            } else {
                cm = m;                
            }
            return;
        }
        if (cg == 0 && cm > 0) {
            if (cm > g) {
                cg = g;
                cm -= g;
            } else {
                cg += cm;
                cm = 0;
            }
            return;
        }
        // cg > 0
        if (cg == g) {
            cg = 0;
            return;
        }
        // cg > 0 && < g
        int lack = g - cg;
        if (cm >= lack) {
            cm -= lack;
            cg = g;
        }
    };
    while (n--) {
        doAction();
    }
    cout << cg << ' '<< cm;
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
