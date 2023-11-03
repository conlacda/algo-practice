// https://cses.fi/problemset/result/6240469/
// Counting Numbers
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1e9 + 7; // 998244353  1000000009  1000000007
#define ld long double
#define int long long

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
// 123 321
    int n1, n2;
    cin >> n1 >> n2;
    std::function<int(int)> cal = [&](int n){
        if (n < 10) return n+1;
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
        vector<vector<vector<vector<int>>>> dp(nstr.size(), vector<vector<vector<int>>>(10, vector<vector<int>>(2, std::vector<int>(2))));
        // [index][digit][constraint][leading_zero] 3245
        dp[0][0][0][1] = 1; // 0xxx
        for (int i=1;i<nstr[0] - '0';i++) {
            dp[0][i][0][0] = 1; // 1xxx,2xxx
        }
        dp[0][nstr[0] - '0'][1][0] = 1; // 3xxx
        // Tính toán các chữ số đằng sau
        for (int i=1;i<(int) nstr.size();i++) {
            int prevdigit = nstr[i-1] - '0';
            int curdigit = nstr[i] - '0';
            // Mọi số ko constraint
            for (int p=0;p<=9;p++) {
                for (int c=0;c<=9;c++) {
                    if (c == 0 && p == 0) {
                        dp[i][c][0][1] += dp[i-1][p][0][1]; // 00xx 
                    } else
                    if (c != p) {
                    // điều kiện 2 số cạnh nhau khác nhau
                        dp[i][c][0][0] += dp[i-1][p][0][0] + dp[i-1][p][0][1];
                    }
                }
            }
            // Constraint số đằng trước, số đằng sau ko constraint
            for (int c=0;c<curdigit;c++) {
                if (c != prevdigit)
                    // [index][digit][constraint][leading_zero]
                    // dp[i][c][0] += dp[i-1][prevdigit][1];
                    dp[i][c][0][0] += dp[i-1][prevdigit][1][0];
            }
            // Constraint số trước & số sau
            if (curdigit != prevdigit)
                dp[i][curdigit][1][0] += dp[i-1][prevdigit][1][0];
        }
        // In ra kết quả
        int ans = 0;
        for (int d=0;d<=9;d++) {
            ans += dp[nstr.size()-1][d][0][0] + dp[nstr.size()-1][d][0][1]
            + dp[nstr.size()-1][d][1][0] + dp[nstr.size()-1][d][1][1];
        }
        return ans;
    };
    cout << cal(n2) - cal(n1-1);
    show_exec_time();
}
// Hiện tại chưa cần làm gì phức tạp, digit mà kết quả cuối cùng ra bằng giá trị n là được
// [index][digit][constraint]
// Digit thì đúng rồi, nhưng ví dụ n = 3245, k = 0012 -> 12 nhưng không được 
// đếm do 00 có 2 giá trị giống nhau