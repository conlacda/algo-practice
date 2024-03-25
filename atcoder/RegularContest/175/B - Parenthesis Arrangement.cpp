// https://atcoder.jp/contests/arc175/tasks/arc175_b
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    /*
    dp??
    remove tất cả những ngoặc đúng đi, những ngoặc này không cần
    */
    string removed = "";
    for (auto&v: s) {
        if (removed == "") removed += v;
        else {
            if (v == ')' && removed.back() == '(') {
                removed.pop_back();
            } else {
                removed += v;
            }
        }
    }
    s = removed;
    dbg(s);
    if (s.size() == 0) {
        cout << 0;
        return 0;
    }
    // pattern sẽ có dạng ))))((((( 1 loạt đóng rồi tới 1 loạt mở
    int open = 0, close = 0;
    for (auto&v: s) {
        if (v == '(') open++;
        else close++;
    }
    if (a >= 2 * b) {
        // đổi chỗ từng cái là xong
        if (open % 2 == 0) {
            cout << b * (open + close) / 2;
        } else {
            cout << b * open / 2 + b * close / 2 + b;
        }
    } else {
        // Cố để dùng swap tối đa có thể rồi mới dùng sang chuyển 1 cái
        // swap đầu cuối cho tới khi hết 1 loại ngoặc
        int ans = 0;
        int m = min(open, close);
        if (m % 2 == 0) {
            ans = m/2 * a + (open + close - 2 * m) / 2* b;
        } else {
            ans += m/2*a;
            int cur = open + close - 4 * (m/2);
            ans += a;
            cur -= 2;
            ans += cur /2 * b;
        }
        cout << ans;
    }
    show_exec_time();
}
