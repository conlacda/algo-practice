// https://atcoder.jp/contests/abc344/tasks/abc344_f
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

int divCeil(int a, int b) {
    return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}


signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<int>> p(n, vector<int>(n));
    for (auto&row: p)
        for (auto&v: row) cin >> v;
    vector<vector<int>> r(n, vector<int>(n-1));
    vector<vector<int>> d(n-1, vector<int>(n));
    for (auto&row: r)
        for (auto&v: row) cin >> v;
    for (auto&row: d)
        for (auto&v: row) cin >> v;
    /*
    Dùng dp
    dp[row][col][max_point] = {operation, remain_point}
    dp[row][col] = max(dp[row-1][col], dp[row][col-1])
    */
    vector dp(n, vector(n, map<int, pair<int,int>>()));
    dp[0][0][p[0][0]] = {0, 0};
    // transition
    for (int row=0;row<n;row++) {
        for (int col=0;col<n;col++) {
            // top to down
            if (row >=1) {
                for (auto [mp, op_rm]: dp[row-1][col]) { // max_point, operation_cnt, remaining_point
                    auto [op, rm] = op_rm;
                    // đứng tại 1 điểm cho tới khi thừa điểm
                    if (rm < d[row-1][col]) {
                        int stay = divCeil(d[row-1][col] - rm, mp);
                        rm += stay * mp;
                        op += stay;
                    }
                    // đi qua cầu - giảm remaining money và tăng operation lên 1
                    rm -= d[row-1][col]; op++;
                    // tại đây quyết định xem có nên đi từ trên xuống không
                    int newMp = max(mp, p[row][col]);
                    // chưa có đường nào tới thì đi thẳng vào
                    if (dp[row][col].count(newMp) == 0)
                        dp[row][col][newMp] = {op, rm};
                    else {
                        // có đường tới rồi thì phải so sánh
                        /*
                        Quy tắc so sánh:
                        Ta có op và rm là số lượng operation và remain money khi đặt chân tới điểm (row, col)
                        Với diểm có sẵn (đi từ đường khác tới) là cur_op và cur_rm
                        Tại đây ta quy hết thành point. Ví dụ op = 3, rm = 2 và cur_op = 4, rm = 1 với newMp = 5
                        ta thấy op = 3 có thể thêm được 1 op nữa và nó sẽ thành op = 4 và rm = 2 + 5(newMp) = 7
                        point hiện tại là 4 + 1 = 5 -> rõ ràng đi từ điểm row-1, col tới sẽ có nhiều điểm hơn.
                        khi quy ra số điểm mà bằng nhau. Để giảm thiểu lượng operation ta sẽ chọn cái có operation nhỏ hơn.
                        */
                        int oldPoint = rm;
                        auto [cur_op, cur_rm] = dp[row][col][newMp];
                        int curPoint = cur_rm;
                        // quy ra số điểm, điểm sẽ cộng với sự chênh lệch operation * new Maxpoint
                        if (op < cur_op) {
                            oldPoint += (cur_op - op) * newMp;
                        } else curPoint += (op - cur_op) * newMp;
                        // nếu oldPoint hơn điểm thì lấy oldPoint
                        if (oldPoint > curPoint) {
                            dp[row][col][newMp] = {op, rm};
                        } else if (oldPoint == curPoint) {
                            // nếu oldpoint bằng và op nhỏ hơn thì mới đi vào
                            if (op < cur_op) dp[row][col][newMp] = {op, rm};
                        }
                    }
                }
            }
            // left to right - hoàn toàn tương tự như block trên ngoài trừ row-1, col -> row, col-1 và d->r
            if (col >= 1) {
                for (auto [mp, op_rm]: dp[row][col-1]) {
                    auto [op, rm] = op_rm;
                    // đứng tại 1 điểm cho tới khi thừa điểm
                    if (rm < r[row][col-1]) {
                        int stay = divCeil(r[row][col-1] - rm, mp);
                        rm += stay * mp;
                        op += stay;
                    }
                    // đi qua cầu
                    rm -= r[row][col-1]; op++;
                    // tại đây quyết định xem có nên đi từ trên xuống không
                    int newMp = max(mp, p[row][col]);
                    // chưa có đường nào tới thì đi thẳng vào
                    if (dp[row][col].count(newMp) == 0)
                        dp[row][col][newMp] = {op, rm};
                    else {
                        // có đường tới rồi thì phải so sánh
                        int oldPoint = rm;
                        auto [cur_op, cur_rm] = dp[row][col][newMp];
                        int curPoint = cur_rm;
                        if (op < cur_op) {
                            oldPoint += (cur_op - op) * newMp;
                        } else curPoint += (op - cur_op) * newMp;
                        if (oldPoint > curPoint) {
                            dp[row][col][newMp] = {op, rm};
                        } else if (oldPoint == curPoint) {
                            if (op < cur_op) dp[row][col][newMp] = {op, rm};
                        }
                    }
                }
            }
        }
    }
    int ans = INF;
    for (auto [_, op_rm]: dp[n-1][n-1]) {
        auto [op, rm] = op_rm;
        ans = min(ans, op);
    }
    cout << ans;
    show_exec_time();
}
