// [Atcoder|Codeforces].abcxxx.F
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

std::vector<pair<int,int>> range = {
    {1, 1}, {100, 109}, {10000, 10099}, {1000000, 1000999}, {100000000, 100009999},
    {10000000000, 10000099999}, {1000000000000, 1000000999999}, {100000000000000, 100000009999999},
    {10000000000000000, 10000000099999999}, {1000000000000000000, 1000000000000000000},
    {90, 99}, {9900, 9999}, {999000, 999999}, {99990000, 99999999}, {9999900000, 9999999999},
    {999999000000, 999999999999}, {99999990000000, 99999999999999}, {9999999900000000, 9999999999999999},
    {999999999000000000, 999999999999999999},
    {80, 80}, {9800, 9800}, {998000, 998000}, {99980000, 99980000}, {9999800000, 9999800000},
    {999998000000, 999998000000}, {99999980000000, 99999980000000}, {9999999800000000, 9999999800000000},
    {999999998000000000, 999999998000000000}
};
void solve() {
    int n;
    cin >> n;
    int ans = 0;
    for (auto [f, s]: range) {
        if (f <= n && n<= s) ans += n - f + 1;
        if (s < n) ans += s - f + 1;
        // dbg(f, s, n, ans);
        if (f > n) break;
    }
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Ta thấy 1 số có n chữ số sẽ là căn của 1 số có 2n-1 hoặc 2n chữ số
    1 số có 3 chữ số có 2 trường hợp
    abc * abc <= abcdef < (abc+1) * (abc+1)
    abc * abc <= abcde < (abc+1) * (abc+1)
    Dựa vào công thức này sẽ tìm ra được các abc, def thỏa mãn
    Tính lần lượt cho từng số lượng chữ số là được

    abc * abc <= abc * 1000 + def < abc*abc+ 2abc+1
    abc * abc <= abc * 1000 + def luôn đúng
    abc * 1000 + def < abc*abc+ 2abc+1
    abc * (998-abc) + def < 1
    abc buộc phải là 999.
    => def - abc < 1
    => def = [0->999] abc = 999
    hoặc abc = 998
    => def < 1 => def = 0

    abc * abc <= abcde <= (abc + 1) * (abc + 1)
    abc * abc <= abc*100+de <= abc * abc + 2 abc + 1
    abc*100+de <= abc * abc + 2 abc + 1 luôn đúng
    abc * abc <= abc*100+de
    => 0 <= abc(100-abc) + de
    => abc là 100. de từ [00->99]
    */
    sort(range.begin(), range.end());
    for (auto v: range) assert(v.first <= v.second);
    dbg(range);
    int n;
    cin >> n;
    while (n--) solve();

    show_exec_time();
}
