// https://atcoder.jp/contests/abc322/tasks/abc322_e
/*
Cho n kế hoạch với k chỉ tiêu cần đạt tối thiếu p point
Mỗi kế hoạch sẽ tốn cost
Hỏi với cost tối thiểu bao nhiêu để hoàn thành kế hoạch (mọi chỉ tiêu đều lớn hơn hoặc bằng p)
*/
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max()/2;

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

vector<ll> toBaseN(ll n, ll base, int fixed_len = -1){
    vector<ll> ans;
    while (n > 0) {
        ans.push_back(n % base);
        n= n/base;  
    }
    if (fixed_len != -1)
        while ((int) ans.size() < fixed_len) ans.push_back(0);
    reverse(ans.begin(), ans.end());
    return ans;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n, k, p;
    cin >> n >> k >> p;
    vector<vector<int>> a(n, vector<int>(k));
    vector<int> cost(n);
    for (int i=0;i<n;i++) {
        cin >> cost[i];
        for (auto &v: a[i]) cin >> v;
    }
    std::function<vector<vector<int>>()> gen = [&](){
        // đoạn này tạo ra [0, 0, 0], [0, 0, 1], ...[5, 5, 5]
        /*
        Tạo ra cái này bản chất là các số bậc 5 (bậc k)
        Các số sẽ bắt đầu từ 0->[5,5,5] bậc k chuyển qua bậc 10
        */
        vector<vector<int>> ans;
        vector<int> final; for (int i=0;i<k;i++) final.push_back(p);
        int cur = 0;
        while (true) {
            auto bs = toBaseN(cur, p+1, k);
            ans.push_back(bs);
            if (bs == final) break;
            cur++;
        }
        return ans;
    };
    auto all = gen(); // đoạn này tạo ra [0, 0, 0], [0, 0, 1], ...[5, 5, 5] 
    /*
    dp[i][vector<>] dp[0][{0, 1, 2, 3, 4}] = 4;
    dp[index - công việc thứ i_th][số điểm hiện có biểu diễn bằng vector<>] = cost
    Bài này bản chất là knapsack nhưng ngoặc thứ 2 là vector thay vì là int
    Việc cộng trừ vector phải for phức tạp hơn cộng trừ int 1 xíu
    */
    vector<map<vector<int>, int>> dp(n+1);
    // Khởi tạo
    for (int i=0;i<n;i++)
        for (auto v: all)
            dp[i][v] = INF;
    vector<int> zero; for (int i=0;i<k;i++) zero.push_back(0);
    dp[0][zero] = 0; // ko làm gì thì ko mất cost
    // Transition
    for (int i=0;i<n;i++) {
        // Không chọn
        dp[i+1] = dp[i];
        // Có chọn
        for (auto v: all) {
            vector<int> got;
            for (int j=0;j<k;j++) {
                int x = a[i][j] + v[j];
                if (x > p) x = p;
                got.push_back(x);
                /*
                Push dp - điểm mấu chốt tại đây là push dp thay vì là pull dp
                Ví dụ kế hoạch đang thực hiện tới đoạn [3, 4, 5], p = 5
                Kế hoạch thứ i có điểm là [2, 4, 0] => làm kế hoạch này sẽ
                ra [5, 8, 5] và sẽ được làm tròn thành [5, 5, 5] tức là
                bằng [p, p, p] để hoàn thành chỉ tiêu.
                Nếu dùng pull dp thì sẽ khó hơn nhiều
                [5, 5, 5] = [3, 1, 0] + [2, 4, 0]
                Ta thấy [3, 1, 0] là điểm cần thiết để hoàn thành nhưng
                nếu dôi ra ví dụ như [4, 1, 0], [3, 5, 2], [3, 4, 5]
                đều thỏa mãn -> khi này công thức transition dp không phải là
                1:1 mà là n:1. n trạng thái trước có thể cùng tạo ra trạng
                thái sau. 
                Push thì 1 trạng thái trước tạo ra 1 trạng thái sau xử lý 1:1 là xong
                */
            }
            dp[i+1][got] = min(dp[i][v] + cost[i], dp[i+1][got]);
        }
    }
    // answer
    int ans = INF;
    vector<int> passed; for (int i=0;i<k;i++) passed.push_back(p);
    for (int i=0;i<=n;i++) {
        ans = min(dp[i][passed], ans);
    }
    if (ans == INF) cout << -1;
    else cout << ans;
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
    thử try catch cho cái dp.at()
*/
