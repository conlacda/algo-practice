#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
// NXFS
    int n, x, f, s;
    cin >> n >> x >> f >> s;
    /*
    Dùng dp để tính dp[day][lines_code]
    với day là index của ngày
        lines_code là số dòng code hiện tại có thể code 
    Vấn đề là chả biết đặt dp có kích thước là bao nhiêu mới đúng
    dp[day][lines_code + S] = dp[day-3][lines_code] + lines_code + S ngủ 3 tiếng năng suất tăng S
    dp[day][lines_code - F] = dp[day-1][lines_code] + lines_code - F
    */
    int maxDay = 100000;
    vector<vector<int>> dp(maxDay, std::vector<int>(x+1, 0));
    // Khởi tạo dp 
    dp[0][x] = x;
    if (x >= n) {
        cout << 1;
        return 0;
    }
    // Transition dp
    for (int day=1;day<maxDay;day++) {
        for (int line=0;line<=x;line++) {
            if (day - 4 >= 0) {
            	if (dp[day - 4][line] != 0) {
                    int d = (line - f <= 0) ? 0: line -f;
	                int k = (d + s >= x) ? x : (d + s);
                    dbg(line);
	                dp.at(day).at(k) = max(dp[day][k], dp[day-4][line] + k);
	                if (dp[day][k] >= n) {
	                    cout << day+1;
	                    return 0;
	                }	
            	}
                
            }
            int k = (line - f <= 0) ? 0 : (line - f); 
            if (dp[day-1][line] == 0) continue;
            dp[day][k] = max(dp[day][k], dp[day -1][line] + k);
            if (dp[day][k] >= n) {
                cout << day+1;
                return 0;
            }
        }
        dbg(day, dp[day]);
    }
    assert(false);
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
*/
