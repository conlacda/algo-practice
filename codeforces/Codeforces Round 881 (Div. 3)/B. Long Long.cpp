// https://codeforces.com/contest/1843/problem/B
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
// const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

void solve() {
    int n;
    cin >> n;
    vector<int> a;
    for (int i=0;i<n;i++) {
        int x;
        cin >> x;
        if (x != 0) a.push_back(x);
    }
    int cnt = 0;
    int ans = 0;
    for (int i=0;i<(int) a.size();i++) {
        if (a[i] < 0 && (i ==0 || a[i-1] >0)) {
            cnt++;
        }
        ans += abs(a[i]);
    }
    cout << ans << ' '<< cnt <<'\n';
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