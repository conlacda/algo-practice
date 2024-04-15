// https://atcoder.jp/contests/abc349/tasks/abc349_f
// F - Subsequence LCM
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
const int maxN = 1e7; // maxN < 1e8 - thỉnh thoảng allocate ko được. 1e9 super slow
#else
#define dbg(...)
const int maxN = 1e8;
#endif

// Check prime number N < 1e18
// https://cp-algorithms.com/algebra/primality_tests.html
bool checkBigPrime(uint64_t n) { // returns true if n is prime, else returns false.
    std::function<uint64_t(uint64_t, uint64_t, uint64_t)> binpower = [&](uint64_t base, uint64_t e, uint64_t mod){
        uint64_t result = 1;
        base %= mod;
        while (e) {
            if (e & 1)
                result = (__uint128_t)result * base % mod;
            base = (__uint128_t)base * base % mod;
            e >>= 1;
        }
        return result;
    };
    std::function<bool(uint64_t, uint64_t, uint64_t, int)> check_composite = [&](uint64_t n, uint64_t a, uint64_t d, int s){
        uint64_t x = binpower(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        for (int r = 1; r < s; r++) {
            x = (__uint128_t)x * x % n;
            if (x == n - 1)
                return false;
        }
        return true;
    };
    if (n < 2) return false;

    int r = 0;
    uint64_t d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == (uint64_t) a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

map<ll, int> primeFactorize(ll n) {
    std::function<ll(int)> pollard_single = [&](ll n) {
        if (checkBigPrime(n)) return n;
        if (n % 2 == 0) return (ll) 2;
        ll st = 0;
        auto f = [&](ll x) { return (__int128_t(x) * x + st) % n; };
        while (true) {
            st++;
            ll x = st, y = f(x);
            while (true) {
                ll p = std::__gcd((y - x + n), n);
                if (p == 0 || p == n) break;
                if (p != 1) return p;
                x = f(x);
                y = f(f(y));
            }
        }
    };
    std::function<vector<ll>(ll)> pollard = [&](ll n) {
        if (n == 1) return vector<ll>{};
        ll x = pollard_single(n);
        if (x == n) return vector<ll>{x};
        vector<ll> le = pollard(x);
        vector<ll> ri = pollard(n / x);
        le.insert(le.end(), ri.begin(), ri.end());
        return le;
    };
    auto factors = pollard(n);
    map<ll, int> res;
    for (auto&v: factors) res[v]++;
    return res;
}

int _pow(int a, int b) {
    int res = 1;
    while (b--) res *= a;
    return res;
}
int power(int a, int b, int m = mod) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    auto mf = primeFactorize(m);
    vector<int> mff;
    for (auto v: mf) mff.push_back(_pow(v.first, v.second));
    int k = (1 << ((int) mf.size())) - 1;
    dbg(k);
    // convert number to bitmask
    vector<int> a;
    for (int i=0;i<n;i++) {
        int x;
        cin >> x;
        if (m % x != 0) continue;
        int bitmask = 0;
        for (int j=0;j<(int) mff.size();j++) {
            if (x % mff[j] == 0) bitmask |= (1 << j);
        }
        a.push_back(bitmask);
    }
    dbg(a);
    n = (int) a.size();
    vector<int> dp(k + 1, 0);
    dp[0] = 1;
    map<int, int> ma; for (int i=0;i<n;i++) ma[a[i]]++;
    for (auto [v, cnt]: ma) {
        vector<int> dpc = dp;
        /*
        mỗi lần -> x -> y thì y->y và x ko thay đổi vì ko có ai chuyển tới
        -> y sau 1 lần = dp[y] + dp[x] + dp[y] = 2y + x
        -> y sau 2 lần = (dp[y] + dp[x] + dp[y]) + dp[x] + (dp[y] + dp[x] + dp[y])
                            = 4y + 3x
        -> y sau 3 lần = (4y+3x) + x + (4y+3x) => 8y + 7x
        1 -> 3 -> 7 -> 15 => 2^n - 1
        nếu coi x là toàn bộ sum chuyển tới y -> k lần = dp[y] + sum * (2^n-1)
        */
        for (int mask=0;mask<=k;mask++) {
            dpc[mask | v] += dp[mask] * (power(2, cnt, mod) - 1);
            dpc[mask | v] %= mod;
        }
        dp = dpc;
    }
    if (k == 0) {
        cout << dp[k] - 1; // nếu k sẵn bằng 0 thì ko chọn gì cũng ra 0 -> loại bỏ đoạn ko chọn gì
    } else {
        cout << dp[k];
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Cẩn thận trường hợp:
1. k = 0?? -> ko chọn gì thì hàm or cũng ra 0 = k và được đếm thành 1 lần
2. a = {} -> ko có số nào được chọn vào -> return 0
*/
