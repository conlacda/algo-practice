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

// Tìm (x, y) thỏa mãn ax + by = c vs default c = 1 (extend_gcd)
pair<int, int> findSolution(int a, int b, int c = 1) {
    int g = __gcd(a, b);
    a /= g; b /= g; c /= g;
    int x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    x = x * c; y = y * c; // ax+by=1 -> a*x*c+b*y*c=c
    assert(a * x + b * y == c);
    return make_pair(x, y);  
}

bool hasSolution(int a, int b, int c) {
    if (a == b && a == 0) return c == 0; // 0x+0y = 0 != c != 0
    int g = __gcd(a, b);
    if (c % g != 0) return false;
    return true;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int x, y;
    cin >> x >> y;
    if (hasSolution(y, -x, 2)) {
        int x0, y0;
        tie(x0, y0) = findSolution(y, -x, 2); // x0,y0 là 1 nghiệm. a*x0+b*y0=c
        cout << x0 << ' '<< y0;
    } else if (hasSolution(y, -x, -2)) {
        int x0, y0;
        tie(x0, y0) = findSolution(y, -x, -2); // x0,y0 là 1 nghiệm. a*x0+b*y0=c
        cout << x0 << ' '<< y0;
    } else cout << -1;

    show_exec_time();
}
