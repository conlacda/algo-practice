// https://cses.fi/problemset/result/6240469/
// Counting Numbers
 
#include<bits/stdc++.h>
 
#define int long long // __int128
 
using namespace std;
 
#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif
 
#define dpcase(x, y) \
    dp[index][digit][x] += dp[index-1][prevdigit][y]; \
    touch[index][digit][x] = true; \
    if (digit != prevdigit) \
        cnt[index][digit][x] += cnt[index-1][prevdigit][y];
 
// digitDP[index][digit][constraint] constraint: 0/1/2/3 => ko/low/up/low&up constraint
int digitDPSameDigit(string low, string up) {
    dbg(low, up);
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    // dp[index][digit][constraint_0/1/2/3]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(10, vector<int>(4, 0)));
    vector<vector<vector<bool>>> touch(n, vector<vector<bool>>(10, vector<bool>(4, false)));
    int cnt[n][10][4];
    memset(cnt, 0, sizeof(cnt));
    if (up[0] == low[0]) {
        int digit = up[0] - '0';
        dp[0][digit][3] = 1; // 1234 & 1567 => 1xxx
        touch[0][digit][3] = true; // 1234 & 1567 => 
        cnt[0][digit][3] = 1; // 1234 & 1567 => 1xxx
    } else {
        int digit = low[0] - '0';
        dp[0][digit][1] = 1; // 1234 & 3456 => 1xxx
        touch[0][digit][1] = true; // 1234 & 3456 => 1xxx
        cnt[0][digit][1] = 1; // 1234 & 3456 => 1xxx
        for (digit=low[0]-'0'+1;digit<=up[0]-'0'-1;digit++) {
            dp[0][digit][0] = 1; // 2xxx
            touch[0][digit][0] = true; // 
            cnt[0][digit][0] = 1; // 2xxx
        }
        digit = up[0] - '0';
        dp[0][digit][2] = 1; // 3xxx
        touch[0][digit][2] = true; // 3xxx
        cnt[0][digit][2] = 1; // 3xxx        
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
            for (int prevdigit=0;prevdigit<10;prevdigit++) {
                if (!touch[index-1][prevdigit][0]) continue;
                dpcase(0, 0);
            }
 
            int prevdigit = up[index-1] - '0';
            // Constraint trên => ko constraint
            if (digit < up[index] - '0' && touch[index-1][prevdigit][2]) {
                dpcase(0, 2);
            }
            // Constraint trên => tiếp tục constraint
            if (digit == up[index] - '0' && touch[index-1][prevdigit][2]) {
                dpcase(2, 2);
            }
 
            prevdigit = low[index-1] - '0';
            // Constraint dưới => ko constraint
            if (digit > low[index] - '0' && touch[index-1][prevdigit][1]) {
                dpcase(0, 1);
            }
            // Constraint dưới => constraint dưới tiếp
            if (digit == low[index] - '0' && touch[index-1][prevdigit][1]) {
                dpcase(1, 1);
            }
            
            // Constraint 2 chiều => ko constraint
            if (up[index-1] != low[index-1]) continue; // trước đó ko có constraint 2 chiều nữa
            prevdigit = up[index-1] - '0';
            // Constraint 2 chiều hay constraint 1 chiều
            if (up[index] == low[index]) {
                // Constraint 2 chiều tiếp
                if (digit == up[index] - '0' && touch[index-1][prevdigit][3]) {
                    dpcase(3, 3);
                }
            } else {
                // constraint dưới
                if (digit == low[index] - '0' && touch[index-1][prevdigit][3]) {
                    dpcase(1, 3);
                } 
                // không constraint nữa
                if (low[index] - '0' < digit && digit < up[index] - '0' && touch[index-1][prevdigit][3]) {
                    dpcase(0, 3);
                }
                // constraint trên
                if (digit == up[index] - '0' && touch[index-1][prevdigit][3]) {
                    dpcase(2, 3);
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
    std::function<string(int)> full9 = [&](int num_digit){ return string(num_digit, '9');};
    std::function<string(int)> full0 = [&](int num_digit){ return '1' + string(num_digit-1, '0'); };
    
    int ans = 0;
    for (int i=(int)l.size();i<=(int)r.size();i++) {
        string ll = (i > (int) l.size()) ? full0(i) : l;
        string rr = (i < (int) r.size()) ? full9(i) : r;
        ans += digitDPSameDigit(ll, rr);
    }
 
    return ans;
}
 
int digitDP(int l, int r) { return digitDP(to_string(l), to_string(r)); }
 
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
}
