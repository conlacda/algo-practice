// https://www.spoj.com/problems/PR003004/
#include<bits/stdc++.h>

#define int long long // __int128

using namespace std;

// Base digit DP 4 dimensions dp[index][digit][contraint][leading_zero]
int digitDP(int n) { // n = 3245
    // if (n < 10) return n+1;
    // dp[index][digit][contraint][leading_zero]
    // constraint = 1 thì leading_zero luôn = 0
    string nstr = to_string(n);
    // Initial state
    vector<vector<vector<vector<int>>>> dp(nstr.size(), vector<vector<vector<int>>>(10, vector<vector<int>>(2, vector<int>(2, 0))));
    vector<vector<vector<vector<int>>>> sum(nstr.size(), vector<vector<vector<int>>>(10, vector<vector<int>>(2, vector<int>(2, 0))));
    dp[0][0][0][1] = 1; // xxxx => 0xxx
    sum[0][0][0][1] = 0;
    for (int i=1;i<nstr[0] - '0';i++) {
        dp[0][i][0][0] = 1; // xxxx => 1xxx, 2xxx
        sum[0][i][0][0] = i;
    }
    dp[0][nstr[0] - '0'][1][0] = 1; // xxxx => 3xxx
    sum[0][nstr[0] - '0'][1][0] = nstr[0] - '0';
    // Transition
    for (int index=1;index<(int) nstr.size();index++) { // index
        for (int digit=0;digit<=9;digit++) { // digit
            int prev_digit = nstr[index-1] - '0';
            // Constraint - không constraint gì cả
                // > Leading zero - khi 2 số đều bằng 0
            if (digit == 0 && prev_digit == 0) { // 0xxx => 00xx -> không constraint
                dp[index][digit][0][1] += dp[index-1][prev_digit][0][1];
            }
                // Không leading zero tại số hiện tại
            for (int p=0;p<=9;p++) {
                // 1xxx -> 1[0:9]xx    0xxx -> 0[0:9]xx
                dp[index][digit][0][0] += dp[index-1][p][0][0];
                sum[index][digit][0][0] += sum[index-1][p][0][0] + dp[index-1][p][0][0] * digit;
                dp[index][digit][0][0] += dp[index-1][p][0][1];
                sum[index][digit][0][0] += sum[index-1][p][0][1] + dp[index-1][p][0][1] * digit;
            }
            // Constraint số trước và không constraint số sau // 30xx 31xx
                // Số sau phải nhỏ hơn cur_digit để ko bị constraint
            int cur_digit = nstr[index] - '0';
            if (digit < cur_digit) { // 3xxx -> 3[0:2]xx
                dp[index][digit][0][0] += dp[index-1][prev_digit][1][0];
                sum[index][digit][0][0] += sum[index-1][prev_digit][1][0] + dp[index-1][prev_digit][1][0] * digit;
            }
            // Constraint cả số trước và số sau
            if (digit == cur_digit) { // 3xxx -> 32xx
                dp[index][cur_digit][1][0] += dp[index-1][prev_digit][1][0];
                sum[index][cur_digit][1][0] += sum[index-1][prev_digit][1][0] + dp[index-1][prev_digit][1][0] * digit;
            }
        }
    }
    // Get answer
    int ans = 0;
    // dp[index = n.size()-1][all_digit][0/1][0/1]
    for (int digit=0;digit<=9;digit++) {
        ans += sum[(int) nstr.size() -1][digit][0][0];
        ans += sum[(int) nstr.size() -1][digit][0][1];
        ans += sum[(int) nstr.size() -1][digit][1][0];
        ans += sum[(int) nstr.size() -1][digit][1][1];
    }
    return ans;
}
void solve() {
    int l, r;
    cin >> l >> r;
    if (l == 0) cout << digitDP(r) << '\n';
    else
        cout << digitDP(r) - digitDP(l-1) << '\n';
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) solve();
    }
/*
Bài này nếu mà ko dùng mảng sum thêm mà cứ chày cối tính chỉ dựa vào dp
thì sẽ không thể tính được.
Tạo 1 mảng sum có cấu trúc giống hệt dp.
DP sẽ lưu số lượng số
SUM sẽ lưu tổng digit

Transition:
Giả sử có 1 khối [xxx] đã tính được DP, SUM. và giờ xuất hiện thêm 1 số 
hàng đơn vị sau nó => [xxx]k. Ví dụ ta có số n = 3245 và xét tới 324x
khối này sẽ có DP lưu số lượng số, SUM lưu sum tương ứng với khối đó

thêm k vào sau sẽ được:
dp[xxxk] += dp[xxx]
sum[xxxk] += sum[xxx] + dp[xxx] * k.
sum mới sẽ gồm sum của khối cũ. Phần được thêm vào là dp[xxx] lần số k.
dp[xxx] là số lượng số có trong khối đó nên là khối đó sẽ gồm
* Tập khối cũ (đóng nó thành sum[xxx])
* Các digit mới cần được tính sum.
Dễ hình dung hơn giả sử:
xxx = {123, 124}
sum[xxx] = {1+2+3 + 1+2+4}
dp[xxx] = 2
Thêm số 5 vào sẽ thành {1235, 1245}
sum[xxx5] = {1+2+3 + 1+2+4} + 5 * 2
          = sum[xxx]        + k * dp[xxx] 
*/
