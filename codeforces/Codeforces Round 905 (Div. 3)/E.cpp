// https://codeforces.com/contest/1883/problem/E
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

int divCeil(int a, int b) {
  return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}

 int divFloor(int a, int b) {
      return a / b - (((a ^ b) < 0 && a % b != 0) ? 1 : 0);
    }
 int power(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    int ans = 0;
    int number2 = 0;
    for (int i=1;i<n;i++) {
        // Mất bao nhiêu số để số đằng trước nhân ra được số đằng sau
        if (a[i-1] <= a[i]) {
            int num = floor(log2(divFloor(a[i], a[i-1])));
            ans += max(number2 - num, (int) 0);
            number2 -= num; if (number2 < 0) number2 = 0;
        }
        else {
            // a[i-1] > a[i]
            int num = ceil(log2(divCeil(a[i-1], a[i])));
            ans += num + number2;
            number2 += num;
        }
    }
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    while (n--) solve();
    // dbg(ceil((long double) log2(8) / log2(10)));

    
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

Vấn đề ở đây là giữ a[i] và số lượng số 2 mà nó đang mang theo
Giá trị thực là a[i] * 2^k nhưng mà nhân vào sẽ tràn số
nên là giữ độc lập a[i] * 2^k.
Tới số tiếp theo thì so sánh a[i] * 2^k với a[i+1].
Tìm số k mới sao cho a[i] * 2^k <= a[i+1] * 2^k'
*/