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
    cin >> s;
    if (s[0] >= 'a' && s[0] <='z') {
        cout << "No";
        return 0;
    }
    for (int i=1;i<(int) s.size();i++) {
            if (s[i] >= 'A' && s[i] <='Z') {
        cout << "No";
        return 0;
    }
    }
    cout << "Yes";

    show_exec_time();
}

