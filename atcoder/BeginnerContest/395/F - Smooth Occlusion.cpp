// https://atcoder.jp/contests/abc395/tasks/abc395_f
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Cho 2 dãy A, B và số X.
    Giảm Ai, Bi sao cho
    * Ai + Bi = H
    * |Ai - Ai+1| <= X
    
    Tìm H sao cho H lớn nhất
    Thực hiện binary search trên H.
    H dài nhất cũng chỉ dài bằng Ai + Bi nhỏ nhất
    Khi Ai + Bi cắt đi để cho bằng H thì Ai sẽ nhận được 1 khoảng giá trị
    Lặp qua toàn bộ Ai+1 để xem khoảng giá trị đó có thỏa mãn không
    */
    int n, x;
    cin >> n >> x;
    vector<int> a(n), b(n);
    for (int i=0;i<n;i++) {
        cin >> a[i] >> b[i];
    }
    int right = INF;
    for (int i=0;i<n;i++) {
        right = min(right, a[i] + b[i]);
    }
    int left = 0;
    std::function<bool(int)> isGood = [&](int h) {
        // a + b -> mid | 3 + 5 -> 6
        // a + b >= mid -> a >= mid - b
        int mina = max((int) 0, h - b[0]);
        int maxa = min(a[0], h);
        if (mina > maxa) return false;
        for (int i=1;i<n;i++) {
            int newmina = max((int) 0, mina - x);
            mina = max(newmina, h - b[i]);
            int newmaxa = min(h, maxa + x);
            maxa = min(a[i], newmaxa);
            if (mina > maxa) return false;
        }
        return true;
    };
    while (left < right) {
        int mid = (left + right) / 2;
        if (mid * 2 < left + right) mid++;
        if (isGood(mid)) left = mid;
        else right = mid - 1;
    }
    assert(isGood(left));
    int sum = 0;
    for (auto&v: a) sum += v;
    for (auto&v: b) sum += v;
    cout << sum - n * left;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
