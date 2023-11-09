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

int l, r, k;
// digitDP[index][digit][constraint]
int digitDP(int num) { // n = 3245
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
    string nstr = to_string(num);
    int n = nstr.size();
    int sz = min((int) k, (int) 90);

    int cnt[n][10][4][sz][sz];
    for (int i1=0;i1<n;i1++)
    for (int i2=0;i2<10;i2++)
    for (int i3=0;i3<4;i3++)
    for (int i4=0;i4<sz;i4++)
    for (int i5=0;i5<sz;i5++)
        cnt[i1][i2][i3][i4][i5] = 0;
    // vector<vector<vector<int>>> dp(n, vector<vector<int>>(10, vector<int>(2)));// [index][digit][constraint]
    // vector<vector<vector<vector<vector<int>>>>> cnt(n, vector<vector<vector<vector<int>>>>(10, vector<vector<vector<int>>>(4, vector<vector<int>>(sz, vector<int>(sz, 0)))));
    
    for (int i=0;i<nstr[0] - '0';i++) {
        // dp[0][i][0] = 1; // xxxx -> [0->2]xxx
        cnt[0][i][0][i * (int) pow(10, n-1) % k][i % k] = 1; // xxxx -> [0->2]xxx
    }
    // dp[0][nstr[0] - '0'][1] = 1; // 3xxx
    cnt[0][nstr[0] - '0'][1][(nstr[0] - '0')* (int) pow(10, n-1) % k][(nstr[0] - '0') %k] = 1; // 3xxx
    // Tính toán các chữ số đằng sau
    for (int index=1;index<(int) nstr.size();index++) {
        int prevdigit = nstr[index-1] - '0'; // digit tại số n
        int curdigit = nstr[index] - '0'; // digit tại số n
        // Mọi số ko constraint, prev, cur không có, số được chọn có thể tùy ý từ 0..9 
        for (int p=0;p<=9;p++) {
            for (int c=0;c<=9;c++) {
                // dp[index][c][0] += dp[index-1][p][0]; // 2xxx -> 2[0:9]xx
                for (int remain=0;remain<k;remain++) {
                    for (int digit_remain=0;digit_remain<k;digit_remain++) {
                        int new_remain = (c * (int) pow(10, n-1-index) + remain) % k;
                        int new_digit_remain = (digit_remain + c) % k;
                        cnt[index][c][0][new_remain][new_digit_remain] += cnt[index-1][p][0][remain][digit_remain];
                    }
                }
            }
        }
        // Constraint số đằng trước, số đằng sau ko constraint
        // 3245. prevdigit = 3, curdigit = 2 -> số đang có dạng 3xxx. c <=2. Trường hợp này xét c < 2. Khi này sẽ ko bị constraint nữa. 31xx -> xx tự do từ 00..99
        for (int c=0;c<curdigit;c++) {
            // dp[index][c][0] += dp[index-1][prevdigit][1]; // 3xxx -> 3[0:1]xxx
            for (int remain=0;remain<k;remain++) {
                for (int digit_remain=0;digit_remain<k;digit_remain++) {
                    int new_remain = (c * (int) pow(10, n-1-index) + remain) % k;
                    int new_digit_remain = (digit_remain + c) % k;
                    cnt[index][c][0][new_remain][new_digit_remain] += cnt[index-1][prevdigit][0][remain][digit_remain];
                }
            }
        }
        // Constraint số đằng trước và cả số đằng sau. 3245 -> prevdigit = 3, curdigit = 2.
        // dp[index][curdigit][1] += dp[index-1][prevdigit][1]; // 3xxx -> 32xx
        for (int remain=0;remain<k;remain++) {
            for (int digit_remain=0;digit_remain<k;digit_remain++) {
                int new_remain = (curdigit * (int) pow(10, n-1-index) + remain) % k;
                int new_digit_remain = (digit_remain + curdigit) % k;
                cnt[index][curdigit][1][new_remain][new_digit_remain] += cnt[index-1][prevdigit][1][remain][digit_remain];
            }
        }
    }
    // In ra kết quả
    int ans = 0; // sum(cnt[n-1][all_digit][0/1][0][0])
    for (int d=0;d<=9;d++) {
        ans += cnt[nstr.size()-1][d][0][0][0];
        ans += cnt[nstr.size()-1][d][1][0][0];
    }
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
        cout << digitDP(r) - digitDP(l-1) << '\n';
    }
    
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