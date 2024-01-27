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

    string s;
    cin >>s;
    map<char, int> m;
    for (auto v: s) {
        m[v]++;
    }
    int _max = 0;
    char ans;
    for (auto v: m) {
        if (v.second > _max) {
            _max = v.second;
            ans = v.first;
        }
    }
    cout << ans;

    show_exec_time();
}

