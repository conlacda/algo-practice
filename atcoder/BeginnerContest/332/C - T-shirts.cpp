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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int ans = 0;
    int cur1 = 0, cur2 = 0;
    for (auto &v: s) {
        if (v == '1') cur1++;
        else if (v == '2') cur2++;
        else {
            int need = max(cur1-k, (int) 0);
            ans = max(ans, need + cur2);
            cur1 = 0, cur2 = 0;
        }
    }
    int need = max(cur1 -k,(int) 0);
    ans = max(ans, need + cur2);
    cout << ans;
    
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
