// https://codeforces.com/gym/100886/problem/G
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
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

bool smax(int& x, int y) {
    if (x <= y) {
        x = y;
        return true;
    }
    return false;
}
string finalStr = "";
int finalAns = -1;
// digitDP[index][digit][constraint] constraint: 0/1/2/3 => ko/low/up/low&up constraint
int digitDPSameDigit(int l, int r) { // l = 0234, r = 3211
    dbg(l, r);
    string up = to_string(r), low = to_string(l);
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    // dp[index][digit][constraint_0/1/2/3]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(10, vector<int>(4, 0)));
    vector<vector<vector<int>>> prod(n, vector<vector<int>>(10, vector<int>(4, -1)));
    vector<vector<vector<string>>> num(n, vector<vector<string>>(10, vector<string>(4, "")));
    if (up[0] == low[0]) {
        dp[0][up[0] - '0'][3] = 1; // 1234 & 1567 => 1xxx
        prod[0][up[0] - '0'][3] = up[0] - '0'; // 1234 & 1567 => 1xxx
        num[0][up[0] - '0'][3] += up[0]; // 1234 & 1567 => 1xxx
    } else {
        dp[0][low[0] - '0'][1] = 1; // 1234 & 3456 => 1xxx
        prod[0][low[0] - '0'][1] = low[0] - '0'; // 1234 & 3456 => 1xxx
        num[0][low[0] - '0'][1] += low[0]; // 1234 & 3456 => 1xxx
        for (int first_digit=low[0]-'0'+1;first_digit<=up[0]-'0'-1;first_digit++) {
            dp[0][first_digit][0] = 1; // 2xxx
            prod[0][first_digit][0] = first_digit; // 2xxx
            num[0][first_digit][0] += char(first_digit + '0'); // 2xxx
        }
        dp[0][up[0] - '0'][2] = 1; // 3xxx
        prod[0][up[0] - '0'][2] = up[0] - '0'; // 3xxx
        num[0][up[0] - '0'][2] += up[0]; // 3xxx
    }
    /*
    Không constraint => không constraint
    Constraint trên => ko constraint
                    => tiếp tục constraint
    Constraint dưới => ko constraint
                    => tiếp tục constraint
    Constraint 2 chiều => ko constraint
                       => constraint trên
                       => constraint dưới
                       => constraint 2 chiều
    */
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        for (int digit=0;digit<10;digit++) {
            // Không constraint => không constraint
            for (int p=0;p<10;p++) {
                dp[index][digit][0] += dp[index-1][p][0];
                if (smax(prod[index][digit][0], prod[index-1][p][0] * digit)) {
                    num[index][digit][0] = num[index-1][p][0] + char(digit + '0');
                }
            }
            // Constraint trên => ko constraint
            if (digit < up[index] - '0') {
                dp[index][digit][0] += dp[index-1][up[index-1] - '0'][2];
                if (smax(prod[index][digit][0], prod[index-1][up[index-1] - '0'][2] * digit)) {
                   num[index][digit][0] = num[index-1][up[index-1] - '0'][2] + char(digit + '0');
                }
            }
            // Constraint trên => tiếp tục constraint
            if (digit == up[index] - '0') {
                dp[index][digit][2] += dp[index-1][up[index-1] - '0'][2];
                if (smax(prod[index][digit][2], prod[index-1][up[index-1] - '0'][2] * digit)) {
                   num[index][digit][2] = num[index-1][up[index-1] - '0'][2] + char(digit + '0');  
                }
            }
            // Constraint dưới => ko constraint
            if (digit > low[index] - '0') {
                dp[index][digit][0] += dp[index-1][low[index-1] - '0'][1];
                if (smax(prod[index][digit][0], prod[index-1][low[index-1] - '0'][1] * digit)) {
                    num[index][digit][0] = num[index-1][low[index-1] - '0'][1] + char(digit + '0');
                }
            }
            // Constraint dưới => constraint dưới tiếp
            if (digit == low[index] - '0') {
                dp[index][digit][1] += dp[index-1][low[index-1] - '0'][1];
                if (smax(prod[index][digit][1], prod[index-1][low[index-1] - '0'][1] * digit)) {
                    num[index][digit][1] = num[index-1][low[index-1] - '0'][1] + char(digit + '0');
                }
            }
            // Constraint 2 chiều => ko constraint
            if (up[index-1] != low[index-1]) continue; // trước đó ko có constraint 2 chiều nữa
            int prevdigit = up[index-1] - '0';
            // Constraint 2 chiều hay constraint 1 chiều
            if (up[index] == low[index]) {
                // Constraint 2 chiều tiếp
                if (digit == up[index] - '0') {
                    dp[index][digit][3] += dp[index-1][prevdigit][3];
                    if (smax(prod[index][digit][3], prod[index-1][prevdigit][3] * digit)) {
                        num[index][digit][3] = num[index-1][prevdigit][3] + char(digit + '0');
                    }
                }
            } else {
                // constraint dưới
                if (digit == low[index] - '0') {
                    dp[index][digit][1] += dp[index-1][prevdigit][3];
                    if (smax(prod[index][digit][1], prod[index-1][prevdigit][3] * digit)) {
                        num[index][digit][1] = num[index-1][prevdigit][3] + char(digit + '0');
                    }
                }
                // không constraint nữa
                if (low[index] - '0' < digit && digit < up[index] - '0') {
                    dp[index][digit][0] += dp[index-1][prevdigit][3];
                    if (smax(prod[index][digit][0], prod[index-1][prevdigit][3] * digit)) {
                        num[index][digit][0] = num[index-1][prevdigit][3] + char(digit + '0');
                    }
                }
                // constraint trên
                if (digit == up[index] - '0') {
                    dp[index][digit][2] += dp[index-1][prevdigit][3];
                    if (smax(prod[index][digit][2], prod[index-1][prevdigit][3] * digit)) {
                        num[index][digit][2] = num[index-1][prevdigit][3] + char(digit + '0');
                    }
                }
            }
        }
    }

    // cout << ans; // dp[n-1][0:9][0/1/2/3];
    int ans = -1;
    string number = "";
    for (int digit=0;digit<=9;digit++) {
        if (smax(ans, prod[n-1][digit][0]) && (int) num[n-1][digit][0].size() == n) number = num[n-1][digit][0];
        if (smax(ans, prod[n-1][digit][1]) && (int) num[n-1][digit][1].size() == n) number = num[n-1][digit][1];
        if (smax(ans, prod[n-1][digit][2]) && (int) num[n-1][digit][2].size() == n) number = num[n-1][digit][2];
        if (smax(ans, prod[n-1][digit][3]) && (int) num[n-1][digit][3].size() == n) number = num[n-1][digit][3];
    }
    if (smax(finalAns, ans)) {
        finalStr = number;
    }
    return ans;
}

int digitDP(int l, int r) {
    int ans = 0;
    string ls = to_string(l), rs = to_string(r);
    if ((int) ls.size() == (int) rs.size()) ans += digitDPSameDigit(l, r);
    else {
        ans += digitDPSameDigit(l, (int) pow(10, ls.size()) - 1);
        for (int i=(int) ls.size()+1;i<(int) rs.size();i++) {
            ans += digitDPSameDigit((int) pow(10, i-1) , (int) pow(10, i)-1);
        }
        ans += digitDPSameDigit((int) pow(10, (int) rs.size() -1), r);
    }
    return ans;
}
/** Comment xem tại github */

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int l, r;
    cin >> l >> r;
    digitDP(l, r);
    /*
    Tìm ra số có tích các chữ số lớn nhất
    => tách thành các đoạn -> tìm từng đoạn 1.

    */
    cout << finalStr;
    
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