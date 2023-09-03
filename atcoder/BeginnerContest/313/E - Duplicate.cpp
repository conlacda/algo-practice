#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

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
    int n;
    cin >> n;
    string s;
    cin >> s;
    dbg(s);
    for (int i=0;i<(int) s.size() -1;i++) {
        if (s[i] > '1' && s[i +1] > '1') {
            cout << -1;
            return 0;
        }
    }
    int ans = 0;
    for (int i=(int) s.size()-1;i>0;i--) {
        if (s[i] == '1') {
            ans = ans + 1;
        } else {
            ans = (ans + 1) * (s[i] - '0'); // đây là công thức ngắn gọn chứ ko phải công thức theo suy luận
            // ans + 1 - xóa số lớn hơn 1 đó đi.
            // s[i] - '0' là số lượng phần tử nó sỉnh ra trong 1 lần
            // 21312 -> 2111311 -> 21111131 -> 211111113
            // 2111111111 -> 211111111 -> 21111111 -> 2111111
            // 211111 -> 21111 -> 2111 -> 211 -> 21 -> 2
            // Mỗi lần số 3 kia sẽ thêm 2 số 1 vào (3-1)
            // Xóa số 1 mất 1 lần + xóa các số 1 đó mất ans * (s[i] - 1) lần
        }
        ans %= mod;
    }
    cout << ans;
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.
https://atcoder.jp/contests/abc313/tasks/abc313_e
*/
