// https://atcoder.jp/contests/abc346/tasks/abc346_b
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
    string f = "wbwbwwbwbwbw";
    string s = "";
    while (s.size() < 300) s += f;
    int w, b;
    cin >> w >> b;
    int curw = 0, curb = 0;
    for (int i=0;i<w+b;i++)
        if (s[i] == 'w') curw++;
        else curb++;

    for (int i=w+b;i<(int) s.size();i++) {
        if (s[i] == 'w') curw++;
        else curb++;
        if (s[i-w-b] == 'w') curw--;
        else curb--;
        if (curb == b && curw == w) {
            cout << "Yes";
            return 0;
        }
    }
    cout << "No";
    show_exec_time();
}
