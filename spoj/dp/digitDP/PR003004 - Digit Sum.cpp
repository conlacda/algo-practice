// https://www.spoj.com/problems/PR003004/
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

#define init(cs) \
cnt[0][cs] += 1; \
sum[0][cs] += d;\

#define transition(cur, prev) \
if (cnt[index-1][prev] != 0) { \
    cnt[index][cur] += cnt[index-1][prev]; \
    sum[index][cur] += sum[index-1][prev] + cnt[index-1][prev] * d; \
} \

enum CONSTR { none, up };
// digitDP[index][constraint]
int digitDP(string num) {
    int n = (int) num.size();
    // Initial state
    vector<vector<int>> cnt(n, vector<int>(2, 0));
    vector<vector<int>> sum(n, vector<int>(2, 0));
    for (int d=0;d<num[0] - '0';d++) {
        init(CONSTR::none); // ***
    }
    int d = num[0] - '0';
    init(CONSTR::up); // ***
    // Tính toán các chữ số đằng sau
    for (int index=1;index<n;index++) {
        for (int d=0;d<10;d++) {
            transition(CONSTR::none, CONSTR::none); // ***
        }
        for (int d=0;d<num[index]-'0';d++) {
            transition(CONSTR::none, CONSTR::up); // ***
        }

        int d = num[index] - '0';
        transition(CONSTR::up, CONSTR::up); // ***
    }
    dbg(sum);
    // ans += cnt[n-1][0/1]
    int ans = 0;
    ans += sum[n-1][CONSTR::none];
    ans += sum[n-1][CONSTR::up];
    return ans;
}
int digitDP(int n) { return digitDP(to_string(n)); }

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) {
        int l, r;
        cin >> l >> r;
        if (l == 0) cout << digitDP(r) << '\n';
        else cout << digitDP(r) - digitDP(l-1) << '\n';
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
