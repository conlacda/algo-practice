// https://atcoder.jp/contests/abc349/tasks/abc349_d
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
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
#endif

int _log2(int num) {
    int cnt = 0;
    while (num >>=1) cnt++;
    return cnt;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int l, r;
    cin >> l >> r;
    vector<pair<int,int>> lr;
    if (l == 0) {
        int log = _log2(r);
        lr.push_back({0, (int) pow(2, log)});
        l = (int) pow(2, log);
    }
    // 2**i * j -> 2**i * (j+1)
    int cur = l;
    while (cur < r) {
        int j = cur;
        // cur = 2**i * j
        // tính số i, j
        // nếu ko thỏa mãn thì giảm dần i đi rồi tăng j lên
        int i = 0;
        while (j % 2 == 0) {
            i++;
            j /= 2;
        }
        while ((int) pow(2, i) * (j +1) > r) {
            i--;
            j *= 2;
        }
        dbg(cur, i, j);
        lr.push_back({cur, (int) pow(2, i) * (j +1)});
        cur = (int) pow(2, i) * (j +1);
    }
    cout << lr.size() << '\n';
    for (auto&v: lr) {
        cout << v.first << ' ' << v.second << '\n';
    }
    dbg(lr);

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
