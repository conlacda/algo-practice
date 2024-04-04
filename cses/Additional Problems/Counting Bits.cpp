// https://cses.fi/problemset/task/1146
// Same to https://www.spoj.com/problems/PR003004/
// Idea: sum of digit but in base 2 with digit from 0..1
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

vector<int> toBaseN(int n, int base, int fixed_len = 1) {
    if (n == 0) return vector<int>(fixed_len, 0);
    vector<int> ans;
    while (n > 0) {
        ans.push_back(n % base);
        n= n/base;  
    }
    while ((int) ans.size() < fixed_len) ans.push_back(0);
    reverse(ans.begin(), ans.end());
    return ans;
}

enum C { none, up }; // constraint
// digitDP[index][constraint]
int digitDP(string num) {
    int n = (int) num.size();
    // Initial state
    vector cnt(n, vector<int>(2, 0)); // cnt[index][constraint]// ***
    vector dp(n, vector<int>(2, 0));
    // vector dp(3, vector(4, vector<int>(5, 0))); // dp[3][4][5] full 0 - sử dụng code cho nhanh
    for (int d=0;d<num[0] - '0';d++) {
        cnt[0][C::none] += 1;// ***
        dp[0][C::none] += d;
    }

    int d = num[0] - '0';
    cnt[0][C::up] += 1;// ***
    dp[0][C::up] += d;
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        for (int d=0;d<2;d++) {
            // C::none <- C::none// ***
            if (cnt[index-1][C::none] != 0) {
                cnt[index][C::none] += cnt[index-1][C::none];
                dp[index][C::none] += dp[index-1][C::none] + cnt[index-1][C::none] * d;
            }
        }
        
        for (int d=0;d<num[index]-'0';d++) {
            // C::none <- C::up// ***
            if (cnt[index-1][C::up] != 0) {
                cnt[index][C::none] += cnt[index-1][C::up];
                dp[index][C::none] += dp[index-1][C::up] + cnt[index-1][C::up] * d;
            }
        }

        int d = num[index] - '0';
        // C::up <- C::up// ***
        if (cnt[index-1][C::up] != 0) {
            cnt[index][C::up] += cnt[index-1][C::up];
            dp[index][C::up] += dp[index-1][C::up] + cnt[index-1][C::up] * d;
        }
    }
    int ans = dp[n-1][C::up] + dp[n-1][C::none]; // dp[n-1][0/1]
    return ans;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    digitDP but with digit in 0..1 instead of 0..9
    */
    int n;
    cin >> n;
    string s = "";
    for (auto v: toBaseN(n, 2)) {
        s += v + '0';
    }
    cout << digitDP(s);
    // -> sort of digitDP problem


    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
00
01
10
11

0x
1x
*/
