// https://atcoder.jp/contests/abc243/tasks/abc243_g
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

int SQRT(int n) {
    auto s = (int) sqrt(n);
    if (s * s > n) s--;
    return s;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int maxN = 1e5;
    vector<int> f(maxN, 0), prefixf(maxN, 0);
    vector<int> pprefix(maxN, 0);
    std::function<void()> precompute = [&]() {
        f[1] = 1;
        prefixf[1] = 1;
        for (int i=2;i<maxN;i++) {
            f[i] = prefixf[(int) sqrt(i)];
            prefixf[i] = prefixf[i-1] + f[i];
        }
        for (int i=1;i<maxN;i++) {
            pprefix[i] = pprefix[i-1] + prefixf[i] * (2*i+1);
        }
    };
    precompute();
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        /*
        f(n) = f(1) + f(2) + ... + f(sqrtN)
        f(n) = prefix_sum(f(1) ... f(sqrtN))
        Với n < 1e10 -> sqrt ~ 1e5 thì dễ dàng xử lý
        N > 1e10. Giả sử 1e18.
        f(1e18) = f(1) + f(2) +... + f(1e9)
        Xét mỗi f(k) bên vế phải. f(k) = f(1) + f(2) + ... + f(sqrtK) = prefix_sum[sqrtK]
        Ta thấy với k = i^2 tới (i+1)^2-1. sqrtK là cùng 1 số và f(k) sẽ cùng là prefix_sum[sqrtK]
        => prefix_sum[sqrtK] sẽ xuất hiện (i+1)^2-1-i^2 = 2*i+1 lần
        */
        int sqrtN = SQRT(n);
        int ssqrtN = SQRT(sqrtN);
        int remain = sqrtN - ssqrtN * ssqrtN + 1;
        dbg(n, remain);
        cout << pprefix[ssqrtN-1] + remain * prefixf[ssqrtN] << '\n';
    }

    show_exec_time();
}
