// https://atcoder.jp/contests/abc307/tasks/abc307_e
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 998244353; // 998244353  1000000009  1000000007
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

const int maxN = 1000003;
vector<ll> f, finv;
void cal_factor() { std::function<vector<ll>(int)> mod_inv_range = [&](int sz){ vector<ll> inv(sz, 1); for (int i=2;i<sz;i++){ inv[i] = mod - (mod/i) * inv[mod%i] % mod;} return inv;}; f.resize(maxN, 1); finv.resize(maxN, 1); vector<ll> inv = mod_inv_range(maxN); for (ll i=1;i <= (int) f.size();i++){ f[i] = (f[i-1] * i) % mod; finv[i] = (finv[i-1] * inv[i]) %mod;}}

template<uint mod = mod>
struct mint {
    friend std::ostream& operator<<(std::ostream& os, const mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, mint &s) { return os >> s.x;}
    uint x;
 
    mint() : x(0) {}
    mint(ll _x) { // auto convert ll to mint.
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }
 
    mint& operator += (const mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator -= (const mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator *= (const mint &a) {
        x = (ull)x * a.x % mod;
        return *this;
    }
    mint pow(ll pw) const {
        mint res = 1;
        mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    mint inv() const {
        assert(x != 0);
        uint t = x;
        uint res = 1;
        while(t != 1) {
            uint z = mod / t;
            res = (ull)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }
    mint& operator /= (const mint &a) {
        return *this *= a.inv();
    }
    mint operator + (const mint &a) const {
        return mint(*this) += a;
    }
    mint operator - (const mint &a) const {
        return mint(*this) -= a;
    }
    mint operator * (const mint &a) const {
        return mint(*this) *= a;
    }
    mint operator / (const mint &a) const {
        return mint(*this) /= a;
    }
 
    bool operator == (const mint &a) const {
        return x == a.x;
    }
    bool operator != (const mint &a) const {
        return x != a.x;
    }
    bool operator < (const mint &a) const {
        return x < a.x;
    }
};

using Mint = mint<>; // mint<mod> mint<(int) 1e9+7>

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    /*
    Dùng DP
    Số thứ k sẽ có M-1 cách để phân phối số cho số đó.
    Số thứ N sẽ có M-2 cách để phân phối số cho nó
    Nếu số trước và sau nó trùng nhau thì nó lại có M-1 cách
    dp[index][same_1]; same_1 nghĩa là số đó có giống số ban đầu không.
    Xử lý riêng trường hợp N lẻ, M = 2
    Kết quả sẽ bằng dp[n-1][0] vì số cuối cùng sau dp cần khác số index 0 nữa do đứng vòng tròn
    dp[n-1][1] sẽ có index n-1 và số index 0 trùng nhau
    */
    if (m == 2) {
        if (n % 2== 1) {
            cout << 0;
        } else cout << 2;
        return 0;
    }
    vector<vector<Mint>> dp(n, vector<Mint>(2, 0));
    dp[1][0] = Mint(m-1) * Mint(m);
    for (int i=2;i<n;i++) {
        dp[i][0] += dp[i-1][1] * Mint(m-1); // nếu số đằng trước chọn giống cái ban đầu thì cái đằng sau ko giống ban đầu chắc chắn sẽ khác cái trước và có M-1 cách chọn
        dp[i][0] += (dp[i-1][0]) * Mint(m-2); // 2 số đều chọn khác cái ban đầu thì có m-1(số ban đầu)-1(số đằng trước) = m-2 cách chọn
        dp[i][1] += dp[i-1][0]; // chọn giống số ban đầu thì bằng số cách chọn số đằng trước đó khác số ban đầu
    }
    cout << dp[n-1][0];
    show_exec_time();
}
