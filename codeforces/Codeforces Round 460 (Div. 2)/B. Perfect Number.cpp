// https://codeforces.com/contest/919/problem/B
// Bài này gốc là bruteforce do k nhỏ
// Tại đây dùng digitDP để thực hành, k có thể to hơn 10 000 rất nhiều
// Dùng digitDP để tính từ [0:n] có bao nhiêu số perfect
// Rồi dùng binary search để tìm ra N với [0:N] có k số perfect
#include<bits/stdc++.h>

typedef long long ll;
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

// highlight-next-line
// digitDP[index][digit][constraint][cur_sum] - dùng digitDP 3 dimensions rồi thêm cur_sum vào
int digitDP(int n) { // n = 3245
    /*
    Tính trước hàng đầu tiên
    Từ hàng thứ 2 trở đi tính theo hàng trước đó
    Tính mọi chữ số với dạng ko có constraint - chữ số trước ko constraint, chữ số trước constraint nhưng chữ số sau nhỏ hơn 
    Tính mọi chữ số với dạng có constraint
    => Với từng chữ số tại hàng này tính toán cho nó
    * Chữ số nhỏ hơn chữ số hàng hiện tại (n[index]) thì bằng tổng cả constraint và ko constraint của tất cả mọi số trước đó
    * chữ số bằng n[index] thì ko constraint là tổng của mọi số ko constraint, constraint bằng constraint của chữ số trước đó
    * chữ số > n[index] thì bằng ko constraint của mọi số đằng trước
    */
    // Initial state
    string nstr = to_string(n);
    vector<vector<vector<vector<int>>>> dp(nstr.size(), vector<vector<vector<int>>>(10, vector<vector<int>>(2, vector<int>(12, 0))));
    // highlight-start
    for (int i=0;i<nstr[0] - '0';i++) dp[0][i][0][i] = 1; // xxxx -> [0->2]xxx
    dp[0][nstr[0] - '0'][1][nstr[0] - '0'] = 1; // 3xxx
    // highlight-end
    // Tính toán các chữ số đằng sau
    for (int index=1;index<(int) nstr.size();index++) {
        int prevdigit = nstr[index-1] - '0'; // digit tại số n
        int curdigit = nstr[index] - '0'; // digit tại số n
        // Mọi số ko constraint, prev, cur không có, số được chọn có thể tùy ý từ 0..9 
        for (int p=0;p<=9;p++) {
            for (int c=0;c<=9;c++) {
                // highlight-start
                for (int sum=0;sum<12;sum++)
                    dp[index][c][0][min(sum+c, (int)11)] += dp[index-1][p][0][sum]; // 2xxx -> 2[0:9]xx
                // highlight-end
            }
        }
        // Constraint số đằng trước, số đằng sau ko constraint
        // 3245. prevdigit = 3, curdigit = 2 -> số đang có dạng 3xxx. c <=2. Trường hợp này xét c < 2. Khi này sẽ ko bị constraint nữa. 31xx -> xx tự do từ 00..99
        for (int c=0;c<curdigit;c++) {
            // highlight-start
            for (int sum=0;sum<12;sum++)
                dp[index][c][0][min(sum+c, (int) 11)] += dp[index-1][prevdigit][1][sum]; // 3xxx -> 3[0:1]xxx
            // highlight-end
        }
        // Constraint số đằng trước và cả số đằng sau. 3245 -> prevdigit = 3, curdigit = 2.
        // highlight-start
        for (int sum=0;sum<12;sum++)
            dp[index][curdigit][1][min(sum+curdigit, (int)11)] += dp[index-1][prevdigit][1][sum]; // 3xxx -> 32xx
        // highlight-end
    }
    // In ra kết quả
    int ans = 0; // sum(dp[n-1][all_digit][0/1][cur_sum = 10])
    for (int d=0;d<=9;d++) {
        ans += dp[nstr.size()-1][d][0][10]; // thêm cur_sum = 10
        ans += dp[nstr.size()-1][d][1][10];
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int k; cin >> k;
    int l = 0, r = 1e15;
    while (l != r) {
        int mid = (l + r) /2;
        if (digitDP(mid) >= k) {
            r = mid;
        } else l = mid + 1;
    }
    assert(digitDP(l) == k);
    cout << l;

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
*/