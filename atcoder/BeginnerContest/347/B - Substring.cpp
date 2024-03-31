// https://atcoder.jp/contests/abc347/tasks/abc347_b
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

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
    string s;
    cin >> s;
    int n = s.size();
    set<string> _set;
    for (int i=0;i<n;i++) {
        for (int j=i;j<n;j++) {
            _set.insert(s.substr(i, j-i+1));
        }
    }
    cout << _set.size();

    show_exec_time();
}
