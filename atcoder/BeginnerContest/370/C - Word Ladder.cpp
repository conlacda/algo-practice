// https://atcoder.jp/contests/abc370/tasks/abc370_c
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
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
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s, t;
    cin >> s >> t;
    /*
    Thay đổi những index khác nhau
    nếu đằng trước làm tăng lên thì để sau
    nếu đằng trước làm giảm đi thì làm luôn
    */
    int len = 0;
    for (int i=0;i<(int) s.size();i++ ){
        if (s[i] != t[i]) len++;
    }
    cout << len <<'\n';
    for (int i=0;i<(int)s.size();i++) {
        if (s[i] > t[i]) {
            s[i] = t[i];
            cout << s << '\n';
        }
    }
    for (int i=(int) s.size();i>=0;i--) {
        if (s[i] < t[i]) {
            s[i] = t[i];
            cout << s << '\n';
        }
    }
    

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
