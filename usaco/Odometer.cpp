// http://www.usaco.org/index.php?page=viewproblem2&cpid=435
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


#define dpcase(x, y) \
    dp[index][digit][x] += dp[index-1][prevdigit][y]; \
    touch[index][digit][x] = true; \
    for (int f1=0;f1<n+1;f1++) \
        for (int f2=0;f2<n+1;f2++) \
            cnt[index][digit][x][f1 + (digit == first_d)][f2 + (digit == second_d)] += cnt[index-1][prevdigit][y][f1][f2];

// digitDP[index][digit][constraint] constraint: 0/1/2/3 => ko/low/up/low&up constraint
/*
Tính toán cho từng chữ số 1. 
Do cái này là atleast half nên là nếu 2 số chiếm mỗi số 1 nửa thì sẽ bị trùng
Xét toàn bộ số có 0,1,...9 chứa 1 nửa
Xét từng cặp (0,1), ...(0, 9)...(8, 9) để trừ đi khi 2 số cùng xuất hiện 1 lúc đã được tính 2 lần tại 2 số đó riêng lẻ
*/
int digitDPSameDigit(string low, string up, int first_d, int second_d) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    // dp[index][digit][constraint_0/1/2/3]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(10, vector<int>(4, 0)));
    vector<vector<vector<bool>>> touch(n, vector<vector<bool>>(10, vector<bool>(4, false)));
    int cnt[/*index*/n][/*digit*/10][/*constraint*/4][/*first_digit*/n+1][/*second_digit*/n+1];
    memset(cnt, 0, sizeof(cnt)); // set 0 thì nó set toàn bộ về 0 nhưng !=0 thì cẩn thận
    if (up[0] == low[0]) {
        dp[0][up[0] - '0'][3] = 1; // 1234 & 1567 => 1xxx
        touch[0][up[0] - '0'][3] = true; // 1234 & 1567 => 1xxx
        cnt[0][up[0] - '0'][3][(first_d == up[0] - '0')][(second_d == up[0]-'0')] += 1; // 1234 & 1567 => 1xxx
    } else {
        dp[0][low[0] - '0'][1] = 1; // 1234 & 3456 => 1xxx
        touch[0][low[0] - '0'][1] = true; // 1234 & 3456 => 1xxx
        cnt[0][low[0] - '0'][1][(first_d == low[0] - '0')][(second_d == low[0] - '0')] += 1;

        for (int first_digit=low[0]-'0'+1;first_digit<=up[0]-'0'-1;first_digit++) {
            dp[0][first_digit][0] = 1; // 2xxx
            touch[0][first_digit][0] = true; // 2xxx
            cnt[0][first_digit][0][first_digit == first_d][second_d == first_digit] += 1; // 2xxx
        }
        
        dp[0][up[0] - '0'][2] = 1; // 3xxx
        touch[0][up[0] - '0'][2] = true; // 3xxx
        cnt[0][up[0] - '0'][2][first_d == up[0] - '0'][second_d == up[0] - '0'] += 1; // 3xxx
    }
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

    // cout << ans; // cnt[n-1][0:9][0/1/2/3][half][half];
    int ans = 0;
    int half = n/2;
    if (half * 2 < n) half++;
    for (int last_digit=0;last_digit<=9;last_digit++) {
        for (int f1=0;f1<n+1;f1++) {
            for (int f2=0;f2<n+1;f2++) {
                if (second_d == -1) {
                    if (f1 < half) continue;
                    ans += cnt[n-1][last_digit][0][f1][f2];
                    ans += cnt[n-1][last_digit][1][f1][f2];
                    ans += cnt[n-1][last_digit][2][f1][f2];
                    ans += cnt[n-1][last_digit][3][f1][f2];
                } else {
                    if (f1 == half && f2 == half) {
                        ans -= cnt[n-1][last_digit][0][f1][f2];
                        ans -= cnt[n-1][last_digit][1][f1][f2];
                        ans -= cnt[n-1][last_digit][2][f1][f2];
                        ans -= cnt[n-1][last_digit][3][f1][f2];
                    }
                }
            }
        }
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
    int ans = 0;
    for (int first_digit = 0;first_digit<10;first_digit++) {
        if ((int) l.size() == (int) r.size())
                ans += digitDPSameDigit(l, r, first_digit, -1);
            else {
                ans += digitDPSameDigit(l, full9(l.size()), first_digit, -1);
                for (int i=(int) l.size() +1;i<=(int) r.size() -1;i++) 
                    ans += digitDPSameDigit(full0(i), full9(i), first_digit, -1);
                ans += digitDPSameDigit(full0(r.size()), r, first_digit, -1);
        }
        for (int second_digit=first_digit+1;second_digit<10;second_digit++) {
            if ((int) l.size() == (int) r.size())
                ans += digitDPSameDigit(l, r, first_digit, second_digit);
            else {
                ans += digitDPSameDigit(l, full9(l.size()), first_digit, second_digit);
                for (int i=(int) l.size() +1;i<=(int) r.size() -1;i++) 
                    ans += digitDPSameDigit(full0(i), full9(i), first_digit, second_digit);
                ans += digitDPSameDigit(full0(r.size()), r, first_digit, second_digit);
            }
        }
    }
    return ans;
}

int digitDP(int l, int r) { return digitDP(to_string(l), to_string(r)); }
/** Comment xem tại github */

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        freopen("odometer.in", "r", stdin);
        freopen("odometer.out", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    string l, r;
    cin >> l >> r;
    cout << digitDP(l, r);
    
    show_exec_time();
}
