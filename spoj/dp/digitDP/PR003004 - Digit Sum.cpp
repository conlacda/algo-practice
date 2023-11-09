// https://www.spoj.com/problems/PR003004/
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

// digitDP[index][digit][constraint] constraint: 0/1/2/3 => ko/low/up/low&up constraint
int digitDPSameDigit(string low, string up) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    // dp[index][digit][constraint_0/1/2/3]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(10, vector<int>(4, 0)));
    // highlight-next-line
    vector<vector<vector<int>>> sum(n, vector<vector<int>>(10, vector<int>(4, 0)));
    if (up[0] == low[0]) {
        dp[0][up[0] - '0'][3] = 1; // 1234 & 1567 => 1xxx
        // highlight-next-line
        sum[0][up[0] - '0'][3] = up[0] - '0'; // 1234 & 1567 => 1xxx
    } else {
        dp[0][low[0] - '0'][1] = 1; // 1234 & 3456 => 1xxx
        // highlight-next-line
        sum[0][low[0] - '0'][1] = low[0] - '0'; // 1234 & 3456 => 1xxx

        for (int first_digit=low[0]-'0'+1;first_digit<=up[0]-'0'-1;first_digit++) {
            dp[0][first_digit][0] = 1; // 2xxx
            // highlight-next-line
            sum[0][first_digit][0] = first_digit; // 2xxx
        }
        
        dp[0][up[0] - '0'][2] = 1; // 3xxx
        // highlight-next-line
        sum[0][up[0] - '0'][2] = up[0] - '0'; // 3xxx
    }
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        for (int digit=0;digit<10;digit++) {
            // Không constraint => không constraint
            for (int p=0;p<10;p++) {
                dp[index][digit][0] += dp[index-1][p][0];
                // highlight-next-line
                sum[index][digit][0] += sum[index-1][p][0] + dp[index-1][p][0] * digit;
            }
            // Constraint trên => ko constraint
            if (digit < up[index] - '0') {
                dp[index][digit][0] += dp[index-1][up[index-1] - '0'][2];
                // highlight-next-line
                sum[index][digit][0] += sum[index-1][up[index-1] - '0'][2] + dp[index-1][up[index-1] - '0'][2] * digit;
            }
            // Constraint trên => tiếp tục constraint
            if (digit == up[index] - '0') {
                dp[index][digit][2] += dp[index-1][up[index-1] - '0'][2];
                // highlight-next-line
                sum[index][digit][2] += sum[index-1][up[index-1] - '0'][2] + dp[index-1][up[index-1] - '0'][2] * digit;
            }
            // Constraint dưới => ko constraint
            if (digit > low[index] - '0') {
                dp[index][digit][0] += dp[index-1][low[index-1] - '0'][1];
                // highlight-next-line
                sum[index][digit][0] += sum[index-1][low[index-1] - '0'][1] + dp[index-1][low[index-1] - '0'][1] * digit;
            }
            // Constraint dưới => constraint dưới tiếp
            if (digit == low[index] - '0') {
                dp[index][digit][1] += dp[index-1][low[index-1] - '0'][1];
                // highlight-next-line
                sum[index][digit][1] += sum[index-1][low[index-1] - '0'][1] + dp[index-1][low[index-1] - '0'][1] * digit;
            }
            // Constraint 2 chiều => ko constraint
            if (up[index-1] != low[index-1]) continue; // trước đó ko có constraint 2 chiều nữa
            int prevdigit = up[index-1] - '0';
            // Constraint 2 chiều hay constraint 1 chiều
            if (up[index] == low[index]) {
                // Constraint 2 chiều tiếp
                if (digit == up[index] - '0') {
                    dp[index][digit][3] += dp[index-1][prevdigit][3];
                    // highlight-next-line
                    sum[index][digit][3] += sum[index-1][prevdigit][3] + dp[index-1][prevdigit][3] * digit;
                }
            } else {
                // constraint dưới
                if (digit == low[index] - '0') {
                    dp[index][digit][1] += dp[index-1][prevdigit][3];
                    // highlight-next-line
                    sum[index][digit][1] += sum[index-1][prevdigit][3] + dp[index-1][prevdigit][3] * digit;
                } 
                // không constraint nữa
                if (low[index] - '0' < digit && digit < up[index] - '0') {
                    dp[index][digit][0] += dp[index-1][prevdigit][3];
                    // highlight-next-line
                    sum[index][digit][0] += sum[index-1][prevdigit][3] + dp[index-1][prevdigit][3] * digit;
                }
                // constraint trên
                if (digit == up[index] - '0') {
                    dp[index][digit][2] += dp[index-1][prevdigit][3];
                    // highlight-next-line
                    sum[index][digit][2] += sum[index-1][prevdigit][3] + dp[index-1][prevdigit][3] * digit;
                }
            }
        }
    }

    // cout << ans; // sum[n-1][0:9][0/1/2/3];
    int ans = 0;
    for (int digit=0;digit<=9;digit++) {
        // highlight-start
        ans += sum[n-1][digit][0];
        ans += sum[n-1][digit][1];
        ans += sum[n-1][digit][2];
        ans += sum[n-1][digit][3];
        // highlight-end
    }
    return ans;
}

int digitDP(string l, string r) {
    std::function<string(int)> full9 = [&](int num_digit){
        string res = "";
        for (int i=0;i<num_digit;i++) res += '9';
        return res;
    };
    std::function<string(int)> full0 = [&](int num_digit){
        string res = "1";
        for (int i=0;i<num_digit-1;i++) res += '0';
        return res;
    };
    if ((int) l.size() == (int) r.size())
        return digitDPSameDigit(l, r);
    
    int ans = 0;
    ans += digitDPSameDigit(l, full9(l.size()));
    for (int i=(int) l.size() +1;i<=(int) r.size() -1;i++) 
        ans += digitDPSameDigit(full0(i), full9(i));
    ans += digitDPSameDigit(full0(r.size()), r);
    return ans;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) {
        string l, r;
        cin >> l >> r;
        cout << digitDP(l, r) << '\n';
    }
    
    show_exec_time();
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
