// https://codeforces.com/contest/1928/problem/A
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
    while (n--) {
        int a, b;
        cin >> a >> b;
        int mul = a* b;
        if (mul %2 == 1) {
            cout << "No\n";
            continue;
        }
        if (a > b) swap(a, b);
        if (a % 2 == 0) {
            cout << "Yes\n";
        } else if (b % 2 == 0 && b != 2 * a) {
            cout << "Yes\n";
        } else cout << "No\n";
    }

    show_exec_time();
}
