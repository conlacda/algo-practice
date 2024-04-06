// https://atcoder.jp/contests/abc321/tasks/abc321_f
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Cho 1 loạt bi,
    Thêm bi vào và bớt bi đi.
    Hỏi rằng có bao nhiêu cách chọn để mà sum = K
    Thoạt nhìn nó giống với dynamic connectivity, thêm cạnh, bớt cạnh và đếm số scc
        -> có lẽ có thể giải đc bằng cách này nk phức tạp
    Nếu ko có thao tác xóa -> đơn giản là dp trên 1 set. Sau mỗi index thì in ra giá trị
    
    dp[sum] lưu lại số lần tạo ra được sum từ các số đã cho
    maxSum = 5000 * 5000 nên là ko chạy được nếu mà tính toán toàn bộ sum
    vì mỗi q phải tính lại toàn bộ maxSum -> maxSum * Q = N^3
    -> cần tối ưu
    transition của dp, với push DP
    dp[x+k] += dp[x] với viên bi k -> ko dùng được segtree để giảm thời gian update
    nếu giới hạn lại số lượng update trong 1 query xuống N thì sẽ ok
    -> loại bỏ việc tính toán dp[num > k].
    ví dụ: 3 + 3 + 5 mà k = 10 -> ko tính dp[11] nữa.
    Vì trường hợp thêm 1 viên bi 2 rồi bớt 1 viên 3 sẽ ra 10 nhưng sẽ được tính
    ở trường hợp 3 + 5 + 2 tức là dp[8] -> dp[10].
    Skip dp[num > k] thì mỗi lần chỉ duyệt k tổng -> N * Q => 25*1e6
    lưu ý là duyệt dp ngược từ K -> 1 cho phần thêm bi
    ví dụ 0 + bi 5 -> dp[5] = 1. dp[5] tại đây ko thể push tiếp lên được dp[10]
    mà chỉ push phần trước đó thôi
    và duyệt xuôi 0->k cho phần bớt bi
    ví dụ: có 1 viên bi 5 -> dp[0] = 1, dp[5] = 1, dp[10] = 0
           thêm 1 viên 5 -> dp[10] = 1, dp[5] = 2, dp[0] = 1.
           Nếu duyệt xuôi thì dp[5] = 2 rồi đẩy dp[10] = 2 -> sai
           ngược lại bớt 1 viên 5 đi. Phải bớt từ dp[5] từ 2 về 1 trước
           rồi bớt dp[10] đi dp[5] do 1 viên bớt đi + 1 cách trong dp[5] đều tạo nên được 1 dp[10]
    */
    int q, k;
    cin >> q >> k;
    int maxN = 5005;
    vector<int> dp(maxN+1, 0);
    dp[0] = 1;
    while (q--) {
        char t;
        int num;
        cin >> t >> num;
        dbg(t, num);
        if (t == '+') {
            for (int i=maxN-num;i>=0;i--) {
                // push
                dp[i + num] += dp[i];
                dp[i + num] %= mod;
            }
        } else {
            // t == -
            for (int i=0;i<=maxN-num;i++) {
                dp[i+num] -= dp[i];
                dp[i + num] = (dp[i+num] + mod) % mod;
            }
        }
        cout << dp[k] << '\n';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
