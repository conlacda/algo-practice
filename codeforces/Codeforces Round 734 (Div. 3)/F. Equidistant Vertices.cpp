// https://codeforces.com/contest/1551/problem/F
// F. Equidistant Vertices
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

const int maxN = 1000003;
vector<ll> f, finv; // factorial - giai thừa
unsigned int normalize(int x) { x %= mod; if (x < 0) x += mod; return x; } // there is a weird bug if put this func into mint

template<unsigned int mod = mod>
struct Mint {
    friend std::ostream& operator<<(std::ostream& os, const Mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, Mint &s) { int k; os >> k; s.x = normalize(k); return os; }
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
    Mint operator + (const Mint &a) const {
        return Mint(*this) += a;
    }
    Mint operator - (const Mint &a) const {
        return Mint(*this) -= a;
    }
    Mint operator - () const {
        return Mint(-x);
    }
    Mint operator * (const Mint &a) const {
        return Mint(*this) *= a;
    }
    Mint operator / (const Mint &a) const {
        return Mint(*this) /= a;
    }
    bool operator < (const Mint &a) const {
        return x < a.x;
    }
    
    // Hàm này chỉ chạy với n,r < maxN (~ 1e6)
    Mint nCr(Mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (r < 0 || this->x < r.x) return 0;
        if (f.size() == 0) cal_factorial();
        return Mint(f[x]) * Mint(finv[r.x]) * Mint(finv[x-r.x]);
    }
private:
    void cal_factorial() { std::function<vector<ll>(int)> mod_inv_range = [&](int sz){ vector<ll> inv(sz, 1); for (int i=2;i<sz;i++){ inv[i] = mod - (mod/i) * inv[mod%i] % mod;} return inv;}; f.resize(maxN, 1); finv.resize(maxN, 1); vector<ll> inv = mod_inv_range(maxN); for (ll i=1;i < (int) f.size();i++){ f[i] = (f[i-1] * i) % mod; finv[i] = (finv[i-1] * inv[i]) %mod;}}
};
using mint = Mint<mod>;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (k == 2) {
        cout << mint(n).nCr(2) << '\n';
        return;
    }
    mint ans = 0;
    std::function<void(int)> resolve = [&](int u) {
        vector<vector<int>> data;
        vector<int> curBranch(n, 0);
        std::function<void(int, int, int)> dfs = [&](int u, int p, int len) {
            curBranch[len]++;
            for (auto&v: g[u])
                if (v != p)
                    dfs(v, u, len + 1);
        };
        for (auto&v: g[u]) {
            dfs(v, u, 1);
            data.push_back(curBranch);
            curBranch.assign(n, 0);
        }
        
        std::function<mint(vector<int>)> cal = [&](vector<int> a) {
            // dp[index][remain]
            int n = a.size();
            vector<vector<mint>> dp(n, vector<mint>(k + 1, 0));
            dp[0][k-1] = a[0];
            dp[0][k] = 1; // this is important
            for (int i=1;i<n;i++) {
                for (int remain=1;remain<=k;remain++) {
                    dp[i][remain] += dp[i-1][remain];
                    if (remain - 1 >= 0)
                        dp[i][remain-1] += dp[i-1][remain] * a[i];
                }
            }
            mint ans = 0;
            for (int i=0;i<n;i++)
                ans += dp[i][0];
            return ans;
        };
        for (int depth=1;depth<n;depth++) {
            vector<int> a;
            for (auto&v: data) 
                a.push_back(v[depth]);
            ans += cal(a);
        }
    };
    for (int i=0;i<n;i++)
        resolve(i);
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    for (int i=0;i<t;i++) {
        solve();
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
