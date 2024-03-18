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

void solve() {
    vector<int> a(5), p(5);
    for (auto&v: a) cin >> v;
    for (auto&v: p) cin >> v;
    dbg(a, p);
    // check nếu mà nó lớn hơn sẵn rồi thì ko cần
    int sum = 0;
    int num = 0;
    for (int i=0;i<5;i++) {
        sum += (i+1) * a[i];
        num += a[i];
    }
    if (sum >= 3 * num) {
        cout << "0\n";
        return;
    }
    // Mua thêm x 4 sao và y 5 sao
    /*
    4x+5y+sum >= 3 (num+x+y)
    p[3]*x+p[4]*y min
    => x + 2y + sum >= 3num
    => x + 2y>= 3num-sum với x>=0 và y>=0
    hỏi p[3]*x+p[4]*y min??
    */
    if (p[4] - 2*p[3] >= 0) {
        cout << (3*num-sum) * p[3] << '\n';
    } else {
        // x = 0 || x = 1
        int x =0;
        int y = (3*num-sum) / 2;
        if (y * 2 < 3 *num-sum) y++;
        int ans = p[3] * x+ p[4] * y;
        x =1;
        y = (3*num-sum-1) /2;
        if (y * 2 < 3*num-sum-1) y++;
        ans = min(ans, p[3] * x+ p[4] * y);
        cout << ans << '\n';
    }
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
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
