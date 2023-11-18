#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
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

void solve(){
// cout << "_______\n"; 
    int n, q;
    cin >> n >> q;
    vector<int> d(q);
    for (auto &v: d) cin >> v;
    for (int i=1;i<n;i++) {
        cout << i << ' '<< i+1 << '\n';
    }
    /*
    Coi graph có 2 phần và 1 bridge
    Dịch chuyển bridge đi để được độ dài mong muốn
    */
    pair<int,int> br = {n, n-1};
    for (int i=0;i<q;i++) {
        int di = d[i];
        if (di == n-1) {
            if (br == make_pair(n, n-1)) {
                cout << "-1 -1 -1\n";
            } else {
                cout << br.first << ' '<< br.second << ' '<< n-1 << '\n';
                br = {n, n-1};
            }
        } else {
            if (br.second == di) {
                cout << "-1 -1 -1\n";
            } else {
                cout << br.first << ' '<< br.second << ' '<< di << '\n';
                br.second = di;
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    while (n--) solve();
    
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

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
*/