// [Atcoder|Codeforces].abcxxx.F
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

const int maxN = 1000003;
vector<ll> factorial, factorial_inv; // giai thừa
unsigned int normalize(int x) { x %= mod; if (x < 0) x += mod; return x; } // there is a weird bug if put this func into mint

template<unsigned int mod = mod>
struct Mint {
    friend std::ostream& operator<<(std::ostream& os, const Mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, Mint &s) { int k; cin >> k; os >> k; s.x = normalize(k); return os; }
    unsigned int x;
    Mint() : x(0) {}
    Mint(ll _x) { // auto convert ll to Mint.
        x = normalize(_x);
    }
   
    unsigned int val() { return x; }

    Mint& operator += (const Mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    Mint& operator -= (const Mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    Mint& operator *= (const Mint &a) {
        x = (unsigned long long)x * a.x % mod;
        return *this;
    }
    Mint& operator /= (const Mint &a) {
        return *this *= a.inv();
    }

    Mint power(ll pw) const {
        Mint res = 1;
        Mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    // Chứng minh xem tại CPH - Modular inverse
    Mint inv() const {
        assert(x != 0);
        unsigned int t = x;
        unsigned int res = 1;
        while(t != 1) {
            unsigned int z = mod / t;
            res = (unsigned long long)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }
    
    Mint operator + (const Mint &a) const {
        return Mint(*this) += a;
    }
    Mint operator - (const Mint &a) const {
        return Mint(*this) -= a;
    }
    Mint operator * (const Mint &a) const {
        return Mint(*this) *= a;
    }
    Mint operator / (const Mint &a) const {
        return Mint(*this) /= a;
    }
 
    bool operator == (const Mint &a) const {
        return x == a.x;
    }
    bool operator != (const Mint &a) const {
        return x != a.x;
    }
    bool operator < (const Mint &a) const {
        return x < a.x;
    }
    
    // Hàm này chỉ chạy với n,r < maxN (~ 1e6)
    Mint nCr(Mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (r < 0 || this->x < r.x) return 0;
        if (factorial.size() == 0) cal_factor();
        return Mint(factorial[x]) * Mint(factorial_inv[r.x]) * Mint(factorial_inv[x-r.x]);
    }
    Mint nPr(Mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (x < r.x) return 0; // xC(r.x)
        if (factorial.size() == 0) cal_factor();
        return Mint(factorial[x]) * Mint(factorial_inv[x-r.x]);
    }
private:
    void cal_factor() { std::function<vector<ll>(int)> mod_inv_range = [&](int sz){ vector<ll> inv(sz, 1); for (int i=2;i<sz;i++){ inv[i] = mod - (mod/i) * inv[mod%i] % mod;} return inv;}; factorial.resize(maxN, 1); factorial_inv.resize(maxN, 1); vector<ll> inv = mod_inv_range(maxN); for (ll i=1;i < (int) factorial.size();i++){ factorial[i] = (factorial[i-1] * i) % mod; factorial_inv[i] = (factorial_inv[i-1] * inv[i]) %mod;}}
};
using mint = Mint<mod>;

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int k;
    cin >> k;
    vector<int> a;
    for (int i=0;i<26;i++) {
        int x;
        cin >> x;
        if (x != 0) a.push_back(x);
    }
    // toàn bộ mọi số C = 0
    if ((int) a.size() == 0) {
        cout << 0;
        return 0;
    }
    /*
    Dùng dp[index][curlen] để push lên
    dp[index][curlen] => dp[index+1][curlen+x]
    */
    vector dp((int) a.size(), vector<mint>(k+1, 0));
    for (int i=0;i<=min(a[0], k); i++) {
        dp[0][i]= 1;
    }
    for (int i=0;i<(int) a.size() -1;i++) {
        for (int curlen = 0;curlen<=k;curlen++) {
            for (int next=0;next<=min(k-curlen, a[i+1]);next++) {
                // Đơn giản là nhét next kí tự a[i+1] vào chuỗi đã có curlen kí tự
                // thì ta sẽ được là culen * nCr(curlen+next, curlen)
                // công thức của combinations with repetition
                // https://math.libretexts.org/Courses/Monroe_Community_College/MTH_220_Discrete_Math/7%3A_Combinatorics/7.5%3A_Combinations_WITH_Repetitions
                dp[i+1][curlen+next] += dp[i][curlen] * mint(curlen+next).nCr(curlen);
            }
        }
    }
    mint ans = 0;
    for (int len=1;len<=k;len++) {
        // Kết quả là tổng của các độ dài != 0
        ans += dp[(int) a.size() -1][len];
    }
    cout << ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
có 3 chỗ trống -> có bao nhiêu cách nhét hoa vào 3 chỗ trống
C(n+k−1,k−1)
*/
