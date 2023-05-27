#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

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
    vector<int> coin(n);
    for (int i=0;i<n;i++) cin >> coin[i];
    sort(coin.begin(), coin.end());
    vector<int> ans(k+1, 0);
    // Khoi tao dp
    ans[0] = 1;
    // Tinh dp
    for (auto v: coin) {
        for (int i=1;i<=k;i++){
            if (i-v>=0){
                ans[i] = (ans[i] + ans[i-v]) % mod;
            }
        }
    }

    cout << ans[k];
    show_exec_time();
}
// https://cses.fi/problemset/task/1636/
// Coin Combinations II
/*
- pull dp 
Tính số cách disticnt để tạo ra k.
k = 2+2..+2+3+3+...+3+5+...+5 = 2*x+3*y+5*z. Mỗi cặp (x, y, z) là 1 cách chọn
Tính toàn bộ dp cho 2. rồi tới 3, rồi tới 5. for (v: coin) rồi mới tới for i in(1..k)
*/
