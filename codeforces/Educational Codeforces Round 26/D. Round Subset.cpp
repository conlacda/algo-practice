// https://codeforces.com/contest/837/problem/D
// #pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX
#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)

using namespace std;
using namespace __gnu_pbds;

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
    /*
    dùng dp
    dp[index][remain] = {2, 5}
    chỉ có 2 số 2, 5 ảnh hưởng tới kết quả -> loại bỏ toàn bộ các số không liên quan đi
    số 2, 5 không thể nói số nào quan trọng hơn số nào -> dp[index][remain][0 -> 2 || 1 -> 5]
    */
    int n, k;
    cin >> n >> k;
    vector<int> a;
    for (int i=0;i<n;i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    if ((int) a.size() == 0) {
        cout << 0;
        return 0;
    }
    std::function<pair<int,int>(int)> split = [&](int u) {
        pair<int,int> res = {0, 0}; // {5, 2}
        while (u % 5 == 0) {
            res.first++;
            u /= 5;
        }
        while (u % 2 == 0) {
            res.second++;
            u /= 2;
        }
        return res;
    };
    dbg(a);
    // dp[index][remain][5] = 2
    vector dp(n, vector(k+1, gp_hash_table<int, int>())); // map[<p5, p2>]
    auto pii = split(a[0]);
    dp[0][k-1][pii.first] = pii.second;
    dp[0][k][0] = 0;
    // transition
    for (int i=1;i<n;i++) {
        auto [c5, c2] = split(a[i]);
        for (int remain=0;remain<=k;remain++) {
            for (auto v: dp[i-1][remain]) {
                // not pick
                dp[i][remain][v.first] = max(dp[i][remain][v.first], v.second);
                // pick
                if (remain >= 1)
                    dp[i][remain-1][v.first + c5] = max(dp[i][remain-1][v.first + c5], v.second + c2);
            }
            dp[i-1][remain] = {}; // giảm thiểu memory ko cần thiết từ index đã qua
        }
    }
    // answer dp[n-1][0][...]
    int ans = 0;
    for (auto [c5, c2]: dp[n-1][0]) {
        ans = max(ans, min(c5, c2));
    }
    dbg(ans);
    cout << ans;
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Xác định state: có 4 tham số index, remain - số lượng có thể pick còn lại, p5, p2 là số lượng số 5&2 vì chỉ có 2 số này tạo ra số 0, còn lại thì bỏ qua.
dp[index][remain][map<int/p5, int/p2>]
dp[index][remain][p5] = p2
có 2 trường hợp dp. Tại index i chọn hoặc ko chọn.
* Ko chọn thì dp[index][remain][every p5] = dp[index-1][remain][every p5]
* Chọn thì dp[index-1][remain][p5] => dp[index][remain-1][p5 + cur_num_5] = dp[index-1][remain][p5] + cur_num_2;
    Với mọi cặp p5, c2 tại dp[index-1][remain] thì nếu pick vào index -> remain giảm đi 1, số lượng p5 = p5 + cur_num_5, còn số lượng p2 là giá trị sẽ bằng p2 + cur_num_2 với p2 chính là dp[index-1][remain][p5]
*/
