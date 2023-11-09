// https://lightoj.com/problem/investigation
// TLE: kết quả thì không sao nhưng đoạn loop nhiều quá gây ra TLE
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
// #define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

/*
Tìm ra số lượng số chia hết cho k và tổng các chữ số cũng chia hết cho K
dp[index][digit][constraint][remain][digit_remain]
*/
string l, r; int k;
// digitDP[index][digit][constraint] constraint: 0/1/2/3 => ko/low/up/low&up constraint
int digitDPSameDigit(string low, string up) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    // dp[index][digit][constraint_0/1/2/3]
    int sz = min((int) k, (int) 90);
    int cnt[n][10][4][sz][sz];
    for (int i1=0;i1<n;i1++)
    for (int i2=0;i2<10;i2++)
    for (int i3=0;i3<4;i3++)
    for (int i4=0;i4<sz;i4++)
    for (int i5=0;i5<sz;i5++)
        cnt[i1][i2][i3][i4][i5] = 0;

    // vector<vector<vector<vector<vector<int>>>>> cnt(n, vector<vector<vector<vector<int>>>>(10, vector<vector<vector<int>>>(4, vector<vector<int>>(sz, vector<int>(sz, 0)))));
    if (up[0] == low[0]) {
        cnt[0][up[0] - '0'][3][(up[0] - '0') * (int) pow(10, n-1) % k][(up[0] - '0') % k] = 1; // 1234 & 1567 => 1xxx
    } else {
        cnt[0][low[0] - '0'][1][(low[0]-'0') * (int) pow(10, n-1) % k][(low[0] -'0') % k] = 1; // 1234 & 3456 => 1xxx

        for (int first_digit=low[0]-'0'+1;first_digit<=up[0]-'0'-1;first_digit++) {
            cnt[0][first_digit][0][first_digit * (int) pow(10, n-1) % k][first_digit % k] = 1; // 2xxx
        }
        
        cnt[0][up[0] - '0'][2][(up[0] - '0') * (int) pow(10, n-1) % k][(up[0] - '0') % k] = 1; // 3xxx
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
                for (int remain=0;remain<k;remain++) {
                    for (int digit_remain=0;digit_remain<k;digit_remain++) {
                        int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                        int new_digit_remain = (digit_remain + digit) % k;
                        cnt[index][digit][0][new_remain][new_digit_remain] += cnt[index-1][p][0][remain][digit_remain];
                    }
                }
            }
            // Constraint trên => ko constraint
            if (digit < up[index] - '0') {
                for (int remain=0;remain<k;remain++) {
                    for (int digit_remain=0;digit_remain<k;digit_remain++) {
                        int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                        int new_digit_remain = (digit_remain + digit) % k;
                        cnt[index][digit][0][new_remain][new_digit_remain] += cnt[index-1][up[index-1] - '0'][2][remain][digit_remain];
                    }
                }
            }
            // Constraint trên => tiếp tục constraint
            if (digit == up[index] - '0') {
                for (int remain=0;remain<k;remain++) {
                    for (int digit_remain=0;digit_remain<k;digit_remain++) {
                        int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                        int new_digit_remain = (digit_remain + digit) % k;
                        cnt[index][digit][2][new_remain][new_digit_remain] += cnt[index-1][up[index-1] - '0'][2][remain][digit_remain];
                    }
                }
            }
            // Constraint dưới => ko constraint
            if (digit > low[index] - '0') {
                for (int remain=0;remain<k;remain++) {
                    for (int digit_remain=0;digit_remain<k;digit_remain++) {
                        int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                        int new_digit_remain = (digit_remain + digit) % k;
                        cnt[index][digit][0][new_remain][new_digit_remain] += cnt[index-1][low[index-1] - '0'][1][remain][digit_remain];
                    }
                }
            }
            // Constraint dưới => constraint dưới tiếp
            if (digit == low[index] - '0') {
                for (int remain=0;remain<k;remain++) {
                    for (int digit_remain=0;digit_remain<k;digit_remain++) {
                        int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                        int new_digit_remain = (digit_remain + digit) % k;
                        cnt[index][digit][1][new_remain][new_digit_remain] += cnt[index-1][low[index-1] - '0'][1][remain][digit_remain];
                    }
                }
            }
            // Constraint 2 chiều => ko constraint
            if (up[index-1] != low[index-1]) continue; // trước đó ko có constraint 2 chiều nữa
            int prevdigit = up[index-1] - '0';
            // Constraint 2 chiều hay constraint 1 chiều
            if (up[index] == low[index]) {
                // Constraint 2 chiều tiếp
                if (digit == up[index] - '0') {
                    for (int remain=0;remain<k;remain++) {
                        for (int digit_remain=0;digit_remain<k;digit_remain++) {
                            int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                            int new_digit_remain = (digit_remain + digit) % k;
                            cnt[index][digit][3][new_remain][new_digit_remain] += cnt[index-1][prevdigit][3][remain][digit_remain];
                        }
                    }
                }
            } else {
                // constraint dưới
                if (digit == low[index] - '0') {
                    for (int remain=0;remain<k;remain++) {
                        for (int digit_remain=0;digit_remain<k;digit_remain++) {
                            int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                            int new_digit_remain = (digit_remain + digit) % k;
                            cnt[index][digit][1][new_remain][new_digit_remain] += cnt[index-1][prevdigit][3][remain][digit_remain];
                        }
                    }
                } 
                // không constraint nữa
                if (low[index] - '0' < digit && digit < up[index] - '0') {
                    for (int remain=0;remain<k;remain++) {
                        for (int digit_remain=0;digit_remain<k;digit_remain++) {
                            int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                            int new_digit_remain = (digit_remain + digit) % k;
                            cnt[index][digit][0][new_remain][new_digit_remain] += cnt[index-1][prevdigit][3][remain][digit_remain];
                        }
                    }
                }
                // constraint trên
                if (digit == up[index] - '0') {
                    for (int remain=0;remain<k;remain++) {
                        for (int digit_remain=0;digit_remain<k;digit_remain++) {
                            int new_remain = (digit * (int) pow(10, n-1-index) + remain) % k;
                            int new_digit_remain = (digit_remain + digit) % k;
                            cnt[index][digit][2][new_remain][new_digit_remain] += cnt[index-1][prevdigit][3][remain][digit_remain];
                        }
                    }
                }
            }
        }
    }

    // cout << ans; // cnt[n-1][0:9][0/1/2/3][0][0];
    int ans = 0;
    for (int digit=0;digit<=9;digit++) {
        ans += cnt[n-1][digit][0][0][0];
        ans += cnt[n-1][digit][1][0][0];
        ans += cnt[n-1][digit][2][0][0];
        ans += cnt[n-1][digit][3][0][0];
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
    for (int tc=0;tc<n;tc++) {
        cout << "Case " << tc +1 << ": ";
        cin >> l >> r >>k;
        if (k>90) {
            cout << 0 << '\n';
        } else
        cout << digitDP(l, r) << '\n';
    }
    show_exec_time();
}