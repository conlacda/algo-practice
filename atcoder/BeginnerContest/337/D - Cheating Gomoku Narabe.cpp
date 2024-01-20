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
    int row, col, k;
    cin >> row >> col >> k;
    vector<string> s(row);
    for (auto&v: s) cin >> v;
    dbg(s);
    /*
    Duyệt từng hàng + từng cột 1
    Xét từng hàng -> bò từ đầu hàng bò đi xem có thể đạt đc ko và bao lâu
    */
    std::function<int(string)> cal = [&](string s){
        int ans = INF;
        int cost = 0;
        int last_length = 0;
        int n = s.size();
        if (n < k) return INF;
        // Doc vao phan dau
        for (int i=0;i<k;i++) {
            if (s[i] == 'x') {
                last_length = 0;
            } else if (s[i] == 'o'){
                last_length ++;
            } else {
                // .
                last_length++;
                cost++;
            }
        }
        if (last_length == k) ans = min(ans, cost);
        // doc phan tiep theo
        for (int i=k;i<n;i++) {
            if (s[i] == 'x') {
                if (last_length == k) {
                    ans = min(ans, cost);
                }
                last_length = 0;
                if (s[i-k] == '.') cost--;
            } else {
              // . o  
                if (s[i-k] == '.') {
                    cost--;
                    if (last_length == k) last_length--;
                } else if (s[i-k] == 'o') {
                    if (last_length == k) last_length--;
                }
                if (s[i] == 'o') {
                    last_length++;
                    if (last_length == k) ans = min(ans, cost);
                }
                else {
                    // s[i] == .
                    cost++;
                    last_length++;
                    if (last_length == k) ans = min(ans, cost);
                }
            }
        }
        if (last_length == k) ans = min(ans, cost);
        return ans;
    };
    int ans = INF;
    for (auto v: s) {
        ans = min(ans, cal(v));
    }
    for (int i=0;i<col;i++) {
        string v = "";
        for (int j=0;j<row;j++) {
            v+= s[j][i];
        }
        ans = min(ans, cal(v));
    }
    if (ans == INF) cout << -1;
    else 
        cout << ans;
    show_exec_time();
}
