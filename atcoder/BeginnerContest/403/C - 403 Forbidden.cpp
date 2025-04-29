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
    int n,m,q;
    cin >> n >> m >> q;
    set<int> viewall;
    set<pair<int,int>> viewone;
    while (q--) {
        int t, user;
        cin >> t >> user;
        if (t == 1) {
            int page;
            cin >> page;
            viewone.insert({user, page});
        } else if (t == 2) {
            viewall.insert(user);
        } else if (t == 3) {
            int page;
            cin >> page;
            if (viewall.find(user) != viewall.end()) {
                cout << "Yes\n";
            } else {
                if (viewone.find({user, page}) != viewone.end()) {
                    cout << "Yes\n";
                } else cout << "No\n";
            }
        }
    }


    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Đọc chậm rãi
Viết ra ý tưởng
*/
