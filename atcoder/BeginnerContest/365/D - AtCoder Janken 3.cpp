// https://atcoder.jp/contests/abc365/tasks/abc365_d
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    string s;
    cin >> s;
    // dp[index][val]
    vector<map<int, int>> dp(n, map<int, int>());
    std::function<char(char)> win = [&](char c) {
        if (c == 'R') return 'P';
        if (c == 'P') return 'S';
        return 'R';
    };
    std::function<char(char)> lose = [&](char c) {
        if (c == 'P') return 'R';
        if (c == 'S') return 'P';
        return 'S';
    };
    dp[0][win(s[0])] = 1;
    dp[0][s[0]] = 0;
    // dp[0][lose(s[0])] = 0;
    dbg(dp);
    // Transition
    vector<char> a{'R', 'S', 'P'};
    for (int i=1;i<n;i++) {
        // Ra hơn và khác cái trước thì là thắng
        // dp[i][win(s[i])] dp[i][x]
        for (auto&v: a) {
            if (v != win(s[i])) {
                dp[i][win(s[i])] = max(dp[i][win(s[i])], dp[i-1][v] + 1);
            }
        }
        for (auto&v: a) {
            if (v != s[i])
                dp[i][s[i]] = max(dp[i][s[i]], dp[i-1][v]);

            // Note that the main character never lose, just win or draw
            // if (v != lose(s[i]))
            //     dp[i][lose(s[i])] = max(dp[i][lose(s[i])], dp[i-1][v]);
        }
    }
    // answer
    int ans = 0;
    for (auto&v: dp[n-1]) {
        ans = max(ans, v.second);
    }
    cout << ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
