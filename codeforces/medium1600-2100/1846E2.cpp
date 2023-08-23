#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
// const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

// Bài này dùng cấp số cộng

void solve() {
    int s;
    cin >> s;
    /*
    S = (q^n-1) / (q-1)
    q^n = S * (q-1) + 1
    q^(n-1) ~ S 
    3 <= n <= 60 (2^60 = 10^18, 3 là vì có tối thiểu 3 lần nở hoa)
    min_n = 3 -> max q = 10^9 vì q^2 ~ 10^18
                 min q = 2
    Với mỗi n thì binary search để tìm ra q
    Nếu có cặp (q, n) thỏa mãn thì in ra YES, còn lại in ra NO
    */
    for (int n=3;n<65;n++) {
        int l = 2;
        int r = 1e9+5;
        while (l != r) {
            // (n, l, r): 3 1000005 1000005
            int q = (l + r)/2;
            __int128 right = (__int128) s * (q -1) + 1; // lưu ý cin >> __int128 không hoạt động
            __int128 left = 1;
            for (int i=0;i<n;i++) {
                left = left * q; // do q nhỏ nên không cần dùng binpow
                if (left > right) { // ngắt luôn để tránh left nhân tiếp sẽ bị tràn số ra số âm
                    break;
                }
            }
            // binary search như bình thường
            if (left == right) {
                cout << "YES\n";
                return;
            }
            if (left > right) {
                r = q;
            } else l = q + 1;
        }
    }
    cout << "NO\n";
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) solve();

    
    show_exec_time();
}
// https://codeforces.com/problemset/problem/1846/E2
// E2. Rudolf and Snowflakes (hard version)