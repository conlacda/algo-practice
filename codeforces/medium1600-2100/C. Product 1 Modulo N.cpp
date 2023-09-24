// https://codeforces.com/contest/1514/problem/C
// C. Product 1 Modulo N
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

//friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}

int divCeil(int a, int b) {
    return a / b + (((a ^ b) > 0 && a % b != 0) ? 1 : 0);
}

const int maxN = 1e5; // maxN < 1e8 - lưu ý local chạy max 1e7, OJ max 1e8. 1e9 super slow
class Prime {
private:
    // hàm sàng nguyên tố, có thể tách ra độc lập nếu phần này rườm ra quá
    void build(int n){
        dbg("Nhớ điều chỉnh maxN = căn(N ở đề bài)");
        is_prime.set(); // set to full 1
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; i++)
            if (is_prime[i])
                for (int j = i * i; j <= n; j += i) is_prime[j] = false;
        for (int i=0;i<n;i++) if (is_prime[i]) primes.push_back(i);
    }
    // Calculate a^b
    int power(int a, int b) {
        int res = 1;
        while (b > 0) {
            if (b & 1)
                res = res * a;
            a = a * a;
            b >>= 1;
        }
        return res;
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
            while (u % p == 0) {
                pf[p]++;
                u /= p;
            }
        }
        if (u != 1) pf[u]++;
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
    // Number of factors/divisors 6 % 1,2,3,6 => return 4
    int number_of_divisors(int k) {
        auto pf = split(k);
        int ans = 1;
        for (auto v: pf) ans *= v.second + 1;
        return ans;
    }
    // Tổng toàn số các ước của k
    int sum_of_divisors(int k) {
        auto pf = split(k);
        int ans = 1;
        for (auto v: pf) {
            int factor = v.first, exp = v.second;
            int res = 1;
            for (int i=0;i<=exp;i++) {
                res *= factor;
            }
            res--;
            res /= factor - 1;
            ans *= res;
        }
        return ans;
    }
    // Tích các divisors - warning: rất lớn với k > 100
    int product_of_divisors(int k) {
        return power(k, number_of_divisors(k)/2);
    }
    // Số lượng số 1->k coprime với k
    int number_of_coprime(int k) {
        auto pf = split(k);
        int res = 1;
        for (auto v: pf) {
            int factor = v.first, exp = v.second;
            res *= power(factor, exp - 1) * (factor - 1);
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
    Prime p;
    int n;
    cin >> n;
    /*
    1....n-1 = p chia n dư 1 => tách ra vế thành tích các số nguyên tố 
    thì ko có số nguyên tố nào ở 2 bên trùng nhau. Giả sử 3*.. = nk+1. => n ko thể chia hết cho 3.
    => toàn bộ số bên trái nguyên tố cùng nhau với n
    chỉ xét tới các số nguyên tố cùng nhau với n.
    lấy tích toàn bộ số đó mod cho n ra được k => do k cũng phải là 1 số nguyên tố cùng nhau với n
    bỏ số k khỏi tích là phần dư sẽ thành 1
    */
    vector<int> a(n, false);
    int mul = 1;
    for (int i=1;i<n;i++) {
        if (__gcd(i, n) == 1) {
            a[i] = true;
            mul *= i;
            mul %= n;
        }
    }
    if (mul != 1) {
        assert(a[mul]);
        a[mul] = false;
    }
    int ans = 0;
    for (auto v: a) {
        if (v) ans++;
    }
    cout << ans << '\n';
    for (int i=0;i<n;i++) {
        if (a[i]) {
            cout << i << " ";
        }
    }
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
*/
