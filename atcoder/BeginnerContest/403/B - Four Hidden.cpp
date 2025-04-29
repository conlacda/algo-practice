// #pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s, x;
    cin >> s >> x;
    std::function<bool(int)> isOk = [&](int i) {
        for (int index=0;index<(int) x.size();index++) {
            if (s[index+i] == '?')
                continue;
            if (s[index + i] != x[index])
                return false;
        }
        return true;
    };
    if ((int) s.size() < (int) x.size()) {
        cout << "No";
        return 0;
    }
    for (int i=0;i<(int) s.size();i++) {
        if (isOk(i)) {
            cout << "Yes";
            return 0;
        }
    }
    cout << "No";

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Đọc chậm rãi
Viết ra ý tưởng
*/
