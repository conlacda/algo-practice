#include<bits/stdc++.h>

typedef long long ll; // double long double
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
    int n;
    cin >>n;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
        for (int i=1;i<n;i++) {
            if (a[i] <= a[i-1]) {
                cout << "No";
                return 0;
            }
        }

cout << "Yes";
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}