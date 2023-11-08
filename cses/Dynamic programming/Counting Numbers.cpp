// https://cses.fi/problemset/result/6240469/
// Counting Numbers

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

// digitDP[index][digit][constraint] constraint: 0/1/2/3 => ko/low/up/low&up constraint
int digitDPSameDigit(string low, string up) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    // dp[index][digit][constraint_0/1/2/3]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(10, vector<int>(4, 0)));
    // highlight-next-line
    vector<vector<vector<int>>> cnt(n, vector<vector<int>>(10, vector<int>(4, 0)));
    if (up[0] == low[0]) {
        dp[0][up[0] - '0'][3] = 1; // 1234 & 1567 => 1xxx
        // highlight-next-line
        cnt[0][up[0] - '0'][3] = 1; // 1234 & 1567 => 1xxx
    } else {
        dp[0][low[0] - '0'][1] = 1; // 1234 & 3456 => 1xxx
        // highlight-next-line
        cnt[0][low[0] - '0'][1] = 1; // 1234 & 3456 => 1xxx
        for (int first_digit=low[0]-'0'+1;first_digit<=up[0]-'0'-1;first_digit++) {
            dp[0][first_digit][0] = 1; // 2xxx
            // highlight-next-line
            cnt[0][first_digit][0] = 1; // 2xxx
        }
        dp[0][up[0] - '0'][2] = 1; // 3xxx
        // highlight-next-line
        cnt[0][up[0] - '0'][2] = 1; // 3xxx
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
                if (p != digit)
                    // highlight-next-line
                    cnt[index][digit][0] += cnt[index-1][p][0];
            }
            // Constraint trên => ko constraint
            if (digit < up[index] - '0') {
                dp[index][digit][0] += dp[index-1][up[index-1] - '0'][2];
                if (digit != up[index-1] - '0')
                    // highlight-next-line
                    cnt[index][digit][0] += cnt[index-1][up[index-1] - '0'][2];
            }
            // Constraint trên => tiếp tục constraint
            if (digit == up[index] - '0') {
                dp[index][digit][2] += dp[index-1][up[index-1] - '0'][2];
                if (digit != up[index-1] - '0')
                // highlight-next-line
                    cnt[index][digit][2] += cnt[index-1][up[index-1] - '0'][2];
            }
            // Constraint dưới => ko constraint
            if (digit > low[index] - '0') {
                dp[index][digit][0] += dp[index-1][low[index-1] - '0'][1];
                if (digit != low[index-1] -'0')
                // highlight-next-line
                   cnt[index][digit][0] += cnt[index-1][low[index-1] - '0'][1];
            }
            // Constraint dưới => constraint dưới tiếp
            if (digit == low[index] - '0') {
                dp[index][digit][1] += dp[index-1][low[index-1] - '0'][1];
                if (digit != low[index-1] - '0')
                // highlight-next-line
                    cnt[index][digit][1] += cnt[index-1][low[index-1] - '0'][1];
            }
            // Constraint 2 chiều => ko constraint
            if (up[index-1] != low[index-1]) continue; // trước đó ko có constraint 2 chiều nữa
            int prevdigit = up[index-1] - '0';
            // Constraint 2 chiều hay constraint 1 chiều
            if (up[index] == low[index]) {
                // Constraint 2 chiều tiếp
                if (digit == up[index] - '0') {
                    dp[index][digit][3] += dp[index-1][prevdigit][3];
                    if (digit != prevdigit)
                    // highlight-next-line
                        cnt[index][digit][3] += cnt[index-1][prevdigit][3];
                }
            } else {
                // constraint dưới
                if (digit == low[index] - '0') {
                    dp[index][digit][1] += dp[index-1][prevdigit][3];
                    if (digit != prevdigit)
                    // highlight-next-line
                        cnt[index][digit][1] += cnt[index-1][prevdigit][3];
                }
                // không constraint nữa
                if (low[index] - '0' < digit && digit < up[index] - '0') {
                    dp[index][digit][0] += dp[index-1][prevdigit][3];
                    if (digit != prevdigit)
                    // highlight-next-line
                        cnt[index][digit][0] += cnt[index-1][prevdigit][3];
                }
                // constraint trên
                if (digit == up[index] - '0') {
                    dp[index][digit][2] += dp[index-1][prevdigit][3];
                    if (digit != prevdigit)
                    // highlight-next-line
                        cnt[index][digit][2] += cnt[index-1][prevdigit][3];
                }
            }
        }
    }

    // cout << ans; // cnt[n-1][0:9][0/1/2/3];
    int ans = 0;
    for (int digit=0;digit<=9;digit++) {
        ans += cnt[n-1][digit][0];
        ans += cnt[n-1][digit][1];
        ans += cnt[n-1][digit][2];
        ans += cnt[n-1][digit][3];
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
    cout << std::fixed << setprecision(15);
    string l, r;
    cin >> l >> r;
    cout << digitDP(l, r); 

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
