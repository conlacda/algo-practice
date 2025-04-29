// #pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, d;
    cin >>n >> d;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    int maxN = 1e6 + 5;
    vector<int> m(maxN, 0);
    for (auto&v: a) m[v]++;
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    if (d == 0) {
        cout << n - a.size();
        return 0;
    }
    // dp[index][choose or not]
    /*
    Duyệt từng index 1. Dùng push dp
    Do Ai < 10^6. Dựng nó thành 1 mảng
    Duyệt toàn bộ mảng này.
    Giả sử có chuỗi a[i] -> a[i] + d -> a[i] + 2*d -> ... -> a[i] + k*d
    Chuỗi này bản chất sẽ độc lập so với mọi số khác
    10 2 1 10
    Khi này sẽ chọn 2 số 10 và cắt chuỗi ở giữa thay vì lấy 10->1 || 2 -> 10
    dp[index][choose or not]
    Không chọn số trước thì hiện tại không chọn hay chọn đều được
    Chọn số trước thì sau này không còn chọn được
    dp[i][0] = dp[i-1][1] && dp[i-1][0]
    dp[i][1] = dp[i-1][0]

    Mấu chốt: ko thực hiện dp trực tiếp trên vector<int> a do a[i] có thể ko liên quan tới a[i-1] mà liên quan tới a[i-k]
    nên việc transition trực tiếp ko khả thi
    Chia a làm nhiều phần, mỗi phần bao gồm có cùng số dư khi chia cho d. Rồi thực hiện dp trên đó như mô tả trên.
    */
    std::function<int(int)> solve = [&](int remain) {
        // init
        int n = maxN/d+2;
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = (remain >= m.size()) ? 0: m[remain];
        // transition
        // tối đa lượng được giữ lại
        for (int i=1;i<n;i++) {
            int val = i * d + remain;
            if (val >= (int) m.size() or m[val] == 0) {
                dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
                dp[i][1] = max(dp[i-1][0], dp[i-1][1]);
            } else {
                dp[i][1] = dp[i-1][0] + m[val];
                dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
            }
        }
        // ans
        return max(dp[n-1][0], dp[n-1][1]);
    };
    int ans = 0;
    for (int i=0;i<d;i++) {
        ans += solve(i);
    }
    cout << n - ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
