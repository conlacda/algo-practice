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

enum CONSTR { none, up };

// digitDP[index][constraint]
int digitDP(string num) {
    int n = (int) num.size();
    // Initial state
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(11, 0)));
    for (int d=0;d<num[0] - '0';d++) {
        if (d <= 10)
            dp[0][CONSTR::none][d] += 1; // ***
    }
    int d = num[0] - '0';
    if (d <= 10)
        dp[0][CONSTR::up][d] += 1;
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        for (int d=0;d<10;d++) {
            for (int i=0;i<11;i++) {
                if (d + i <= 10)
                    dp[index][CONSTR::none][d+i] += dp[index-1][CONSTR::none][i];
            }
        }
        for (int d=0;d<num[index]-'0';d++) {
            for (int i=0;i<11;i++) {
                if (i + d <= 10)
                    dp[index][CONSTR::none][d+i] += dp[index-1][CONSTR::up][i];
            }
        }
        int d = num[index] - '0';
        for (int i=0;i<11;i++)
            if (d + i <= 10)
                dp[index][CONSTR::up][d+i] += dp[index-1][CONSTR::up][i];
    }

    // ans += cnt[n-1][0/1]
    int ans = 0;
    ans += dp[n-1][CONSTR::none][10];
    ans += dp[n-1][CONSTR::up][10];
    return ans;
}
int digitDP(int n) { return digitDP(to_string(n)); }

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    /*
    Dùng digitDP và đếm xem có bao nhiêu số k trong khoảng
    Với binary search dễ dàng tìm tới k-th
    */
    int n;
    cin >> n;
    int left = 1, right = 1e18;
    while (left < right) {
        int mid = (left + right) / 2;
        if (digitDP(mid) >= n) {
            right = mid;
        } else left = mid + 1;
    }
    cout << left;
    show_exec_time();
}
