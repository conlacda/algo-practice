// https://lightoj.com/problem/investigation
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

int pow10(int x) {
    return (int) pow(10, x);
}
enum CONSTR { none, up };

// digitDP[index][constraint]
int digitDP(string num, int k) {
    int n = (int) num.size();
    // Initial state
    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(2, vector<vector<int>>(k, vector<int>(k, 0))));
    for (int d=0;d<num[0] - '0';d++) {
        dp[0][CONSTR::none][d*pow10(n-1) % k][d%k] += 1;
    }
    int d = num[0] - '0';
    dp[0][CONSTR::up][d * pow10(n-1) %k][d%k] = 1;
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        int _pow = pow10(n-1-index);
        for (int d=0;d<10;d++) {
            for (int i=0;i<k;i++) {
                for (int j=0;j<k;j++) {
                    dp[index][CONSTR::none][(i + d * _pow) % k][(j+d) %k] += dp[index-1][CONSTR::none][i][j];
                }
            }
        }
        for (int d=0;d<num[index]-'0';d++) {
            for (int i=0;i<k;i++) {
                for (int j=0;j<k;j++) {
                    dp[index][CONSTR::none][(i + d * _pow) % k][(j+d) %k] += dp[index-1][CONSTR::up][i][j];
                }
            }
        }
        int d = num[index] - '0';
        for (int i=0;i<k;i++) {
            for (int j=0;j<k;j++) {
                dp[index][CONSTR::up][(i + d * _pow) % k][(j+d) %k] += dp[index-1][CONSTR::up][i][j];
            }
        }
    }

    // ans += cnt[n-1][0/1]
    int ans = 0;
    ans += dp[n-1][0][0][0];
    ans += dp[n-1][1][0][0];
    return ans;
}
int digitDP(int n, int k) { return digitDP(to_string(n), k); }

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int tc;
    cin >> tc;
    for (int i=0;i<tc;i++) {
        int l, r, k;
        cin >> l >> r >> k;
        if (k>90) {
            cout << "Case " << i + 1<< ": " <<  0 << '\n';
        } else
        cout << "Case " << i + 1<< ": " << digitDP(r, k) - digitDP(l -1, k) << '\n';
    }
    show_exec_time();
}
