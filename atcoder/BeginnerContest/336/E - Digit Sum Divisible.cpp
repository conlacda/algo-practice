// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // ld long double
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

enum CONSTR { none, low, up, both };

// digitDP[index][constraint]
int digitDPSameDigit(string low, string up, int sum) {
    assert(low.size() == up.size() && "Chia làm các khoảng có số chữ số bằng nhau");
    int n = (int) up.size();
    // Initial state
    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(4, vector<vector<int>>(sum, vector<int>(sum +1, 0))));
    if (up[0] == low[0]) {
        int d = up[0] - '0';
        if (d <= sum)
            dp[0][CONSTR::both][d * (int) pow(10, n-1) % sum][d] = 1;
    } else {
        int d = low[0] - '0';
        if (d <= sum)
            dp[0][CONSTR::low][d * (int) pow(10, n-1) % sum][d] = 1;
        for (int first_digit=low[0]-'0'+1;first_digit<=up[0]-'0'-1;first_digit++) {
            if (first_digit <= sum)
                dp[0][CONSTR::none][first_digit * (int) pow(10, n-1) % sum][first_digit] = 1;
        }
        d = up[0] - '0';
        if (d <= sum)
            dp[0][CONSTR::up][d * (int) pow(10, n-1) % sum][d] = 1;
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
        int _pow = (int) pow(10, n-1-index);
        for (int digit=0;digit<10;digit++) {
            for (int i=0;i<sum;i++) {
                for (int j=0;j<=sum - digit;j++) {
                    int new_i = (i+digit*_pow) % sum;
                    // none -> none. Chữ số trước ko constraint thì toàn bộ chữ số sau cũng ko constraint
                    if (dp[index-1][CONSTR::none][i][j] != 0)
                        dp[index][CONSTR::none][new_i][j + digit] += dp[index-1][CONSTR::none][i][j];
                
                    // up -> none
                    if (digit < up[index] - '0' && dp[index-1][CONSTR::up][i][j] != 0)
                        dp[index][CONSTR::none][new_i][j + digit] += dp[index-1][CONSTR::up][i][j];
                    
                    // up -> up
                    if (digit == up[index] - '0' && dp[index-1][CONSTR::up][i][j] != 0)
                        dp[index][CONSTR::up][new_i][j + digit] += dp[index-1][CONSTR::up][i][j];
                    
                    // low -> none
                    if (digit > low[index] - '0' && digit <= 9 && dp[index-1][CONSTR::low][i][j] != 0)
                        dp[index][CONSTR::none][new_i][j + digit] += dp[index-1][CONSTR::low][i][j];
                    
                    // low -> low
                    if (digit == low[index] - '0' && dp[index-1][CONSTR::low][i][j] != 0)
                        dp[index][CONSTR::low][new_i][j + digit] += dp[index-1][CONSTR::low][i][j];

                    // both -> both
                    if (up[index] == low[index] && digit == low[index] - '0' && dp[index-1][CONSTR::both][i][j] != 0)
                        dp[index][CONSTR::both][new_i][j + digit] += dp[index-1][CONSTR::both][i][j];
                    else {
                        // both -> low
                        if (digit == low[index] - '0' && dp[index-1][CONSTR::both][i][j] != 0)     
                            dp[index][CONSTR::low][new_i][j + digit] += dp[index-1][CONSTR::both][i][j];
            
                        // both -> up
                        if (digit == up[index] - '0' && dp[index-1][CONSTR::both][i][j] != 0)
                            dp[index][CONSTR::up][new_i][j + digit] += dp[index-1][CONSTR::both][i][j];
                    
                        // both -> none
                        if (digit > low[index] - '0' && digit < up[index] - '0' && dp[index-1][CONSTR::both][i][j] != 0)
                            dp[index][CONSTR::none][new_i][j + digit] += dp[index-1][CONSTR::both][i][j];
                    }
                }
            }
        }
    }

    // cout << ans; // cnt[n-1][0/1/2/3] dp[n-1][0/1/2/3][0][sum]
    int ans = 0;
    ans += dp[n-1][CONSTR::none][0][sum];
    ans += dp[n-1][CONSTR::low][0][sum];
    ans += dp[n-1][CONSTR::up][0][sum];
    ans += dp[n-1][CONSTR::both][0][sum];
    return ans;
}

int digitDP(string l, string r, int sum) {
    std::function<string(int)> full9 = [&](int num_digit){ return string(num_digit, '9');};
    std::function<string(int)> full0 = [&](int num_digit){ return '1' + string(num_digit-1, '0'); };
    
    int ans = 0;
    for (int i=(int)l.size();i<=(int)r.size();i++) {
        string ll = (i > (int) l.size()) ? full0(i) : l;
        string rr = (i < (int) r.size()) ? full9(i) : r;
        ans += digitDPSameDigit(ll, rr, sum);
    }

    return ans;
}

int digitDP(int l, int r, int sum) { return digitDP(to_string(l), to_string(r), sum); }
/** Comment xem tại github */
/**
 * Phần này chia [l:r] thành các đoạn có cùng số digit.
 * Ví dụ: [12:4321] = [12:99] + [100:999] + [1000:4321]
 * Đếm đoạn to bằng việc đếm các đoạn nhỏ hơn có cùng độ dài digit
 * Khi này ko cần leading_zero
 * dp[index][digit][constraint]
 * index là index tại số đang xét (giống các bài khác) l = 123 => l[0] = 1, l[1] = 2, l[2] = 3
 * digit: digit điền vào cho index đang xét
 * constraint: có 4 loại
 *     * 0: không constraint. [123:256] => 2xx
 *     * 1: constraint cho phần bên dưới. [123:256] => 1xx
 *     * 2: constraint cho phần trên. [123:256] => 2xx
 *     * 3: constraint cho cả low/up. [523:576] => 5xx. low[index] = up[index] = 5 -> số 5 vừa constraint dưới, vừa constraint trên
*/

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    string n_str = to_string(n);
    int MAX_SUM = (int) n_str.size() * 9;
    int ans = 0;
    for (int i=1;i<=MAX_SUM;i++) {
        ans += digitDP(0, n, i);
    }
    cout << ans;
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
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
