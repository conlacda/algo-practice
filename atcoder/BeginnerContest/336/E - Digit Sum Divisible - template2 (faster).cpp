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

enum CONSTR { none, up};

// digitDP[index][constraint]
int digitDP(string num, int sum) {
    int n = (int) num.size();
    // Initial state
    vector<vector<int>> cnt(n, vector<int>(2, 0)); // cnt[index][constraint]
    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(2, vector<vector<int>>(sum, vector<int>(sum +1, 0))));
    for (int d=0;d<num[0] - '0';d++) {
        cnt[0][CONSTR::none] += 1;
        if (d <= sum)
            dp[0][CONSTR::none][d * (int) pow(10, n-1) % sum][d] = 1;
    }
    int d = num[0] - '0';
    cnt[0][CONSTR::up] = 1;
    if (d <= sum)
        dp[0][CONSTR::up][d * (int) pow(10, n-1) % sum][d] = 1;
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        int _pow = (int) pow(10, n-1-index);
        for (int d=0;d<10;d++) {
            for (int i=0;i<sum;i++) {
                for (int j=0;j<=sum - d;j++) {
                    cnt[index][CONSTR::none] += cnt[index-1][CONSTR::none];
                    dp[index][CONSTR::none][(i+d*_pow) % sum][j + d] += dp[index-1][CONSTR::none][i][j];
                }
            }
        }
        for (int d=0;d<num[index]-'0';d++) {
            for (int i=0;i<sum;i++) {
                for (int j=0;j<=sum - d;j++) {
                    cnt[index][CONSTR::none] += cnt[index-1][CONSTR::up];
                    dp[index][CONSTR::none][(i+d*_pow) % sum][j + d] += dp[index-1][CONSTR::up][i][j];
                }
            }
        }
        int d = num[index] - '0';
        for (int i=0;i<sum;i++) {
            for (int j=0;j<=sum - d;j++) {
                cnt[index][CONSTR::up] += cnt[index-1][CONSTR::up];
                dp[index][CONSTR::up][(i+d*_pow) % sum][j + d] += dp[index-1][CONSTR::up][i][j];
            }
        }
    }

    // ans += cnt[n-1][0/1]
    int ans = 0;
    ans += dp[n-1][CONSTR::none][0][sum];
    ans += dp[n-1][CONSTR::up][0][sum];
    return ans;
}
int digitDP(int n, int sum) { return digitDP(to_string(n), sum); }

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    int MAX_SUM = (int) to_string(n).size() * 9;
    int ans = 0;
    for (int i=1;i<=MAX_SUM;i++) {
        ans += digitDP(n, i);
    }
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
