//https://www.spoj.com/problems/FACT0/
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
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

int divCeil(int a, int b) {
    return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}

const int maxN = 1e8; // maxN < 1e8
class Prime {
    // hàm sàng nguyên tố, có thể tách ra độc lập nếu phần này rườm ra quá
    void build(int n){
        is_prime.set(); // set to full 1
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; i++)
            if (is_prime[i])
                for (int j = i * i; j <= n; j += i) is_prime[j] = false;
        for (int i=0;i<n;i++) if (is_prime[i]) primes.push_back(i);
    }
public:
    int n;
    bitset<maxN> is_prime;
    vector<int> primes;
    Prime(int n = maxN) {
        this->n = n;
        build(n);
    }
    bool isPrime(int k) {
        assert(k < n && "Out of range maxN");
        return is_prime[k];
    }
    map<int, int> split(int u) {
        map<int, int> pf; // prime & factor. 12 = 2*2* 3 -> pf[2] = 2, pf[3] = 1
        for (auto p: primes) {
            if (p * p > u) break;
            if (u < maxN && is_prime[u]) break;
            if (u % p == 0) {
                dbg(p);
                while (u % p == 0) {
                    pf[p]++;
                    u /= p;
                }
            }
        }
        if (u != 1) {
            pf[u]++;
        }
        return pf;
    }
    // Danh sách prime từ l->r  r <= maxN^2 ~ 1e14, 1e16, r-l ~ 1e7
    vector<int> primesInRange(int l, int r) {
        int sz = r-l+1;
        vector<bool> ip(sz+1, true);
        for (int i=2;i*i<=r;i++) {
            if (!is_prime[i]) continue;
            for (int j = max(i * i, divCeil(l, i) * i); j <= r; j += i) ip[j-l] = false;
        }
        vector<int> res;
        for (int i=0;i<sz;i++) {
            if (ip[i]) {
                if (i + l > 1) res.push_back(i+l);
            } 
        }
        return res;
    }
};

// Check prime number N < 1e18
// https://cp-algorithms.com/algebra/primality_tests.html
using u64 = uint64_t;
using u128 = __uint128_t;

bool checkBigPrime(u64 n) { // returns true if n is prime, else returns false.
    std::function<u64(u64, u64, u64)> binpower = [&](u64 base, u64 e, u64 mod){
        u64 result = 1;
        base %= mod;
        while (e) {
            if (e & 1)
                result = (u128)result * base % mod;
            base = (u128)base * base % mod;
            e >>= 1;
        }
        return result;
    };
    std::function<bool(u64, u64, u64, int)> check_composite = [&](u64 n, u64 a, u64 d, int s){
        u64 x = binpower(a, d, n);
        if (x == 1 || x == n - 1)
            return false;
        for (int r = 1; r < s; r++) {
            x = (u128)x * x % n;
            if (x == n - 1)
                return false;
        }
        return true;
    };
    if (n < 2) return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == (u64) a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    Prime P;
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        auto s = P.split(n);
        for (auto v: s) {
            cout << v.first << '^' << v.second << ' ';
        }
        cout << '\n';
    }
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
*/
