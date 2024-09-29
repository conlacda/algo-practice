// https://codeforces.com/contest/392/problem/C
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
    Mint operator - () const {
        return Mint(-x);
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
};
using mint = Mint<mod>;

// s[k] = c[0] * s[k-1] + c[1] * f[k-2] + ... 
template<typename T>
T linearRecurrence(const vector<T> &c, const vector<T> &s, long long k) {
    int n = (int) c.size();
    assert(c.size() <= s.size());

    vector<T> a = n == 1 ? vector<T>{c[0]} : vector<T>{0, 1}, x{1};
    // Calculate a * b naively in O(n^2)
    std::function<vector<T>(vector<T>, vector<T>)> mul = [&](const vector<T> &a, const vector<T> &b) {
        vector<T> ret(a.size() + b.size() - 1);
        // ret = a * b
        for (int i=0; i<(int)a.size(); i++)
            for (int j=0; j<(int)b.size(); j++)
                ret[i+j] += a[i] * b[j];
        // reducing ret mod f(x)
        for (int i=(int)ret.size()-1; i>=n; i--)
            for (int j=n-1; j>=0; j--)
                ret[i-j-1] += ret[i] * c[j];
        ret.resize(min((int) ret.size(), n));
        return ret;
    };
    for (; k>0; k/=2) {
        if (k % 2)
            x = mul(x, a);  // mul(a, b) computes a(x) * b(x) mod f(x)
        a = mul(a, a);
    }
    x.resize(n);

    T ret = 0;
    for (int i=0; i<n; i++)
        ret += x[i] * s[i];
    return ret;
}

template<typename T>
vector<T> berlekampMassey(const vector<T> &s) {
    int n = (int) s.size(), l = 0, m = 1;
    vector<T> b(n), c(n);
    T ld = b[0] = c[0] = 1;
    for (int i=0; i<n; i++, m++) {
        T d = s[i];
        for (int j=1; j<=l; j++)
            d += c[j] * s[i-j];
        if (d == 0)
            continue;
        vector<T> temp = c;
        T coef = d / ld;
        for (int j=m; j<n; j++)
            c[j] -= coef * b[j-m];
        if (2 * l <= i) {
            l = i + 1 - l;
            b = temp;
            ld = d;
            m = 0;
        }
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (T &x : c) x = -x;
    return c;
}

template<typename T>
T getKthNumber(const vector<T>& s, int kth) {
    auto c = berlekampMassey<T>(s);
    return linearRecurrence<T>(c, s, kth);
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Cho 1 dãy tìm ra quy luật của nó
    từ quy luật đó tính ra được số thứ k
    dãy chính là tổng chứ ko phải lẻ từng số
    A = F[i] * i^k với k cho sẵn và F chính là dãy Fibonacci
    */
    int n, k;
    cin >> n >> k;
    
    int sampleNum = 1000;
    std::function<vector<mint>()> calFib = [&]() {
        // 1, 1, 2, 3, 5
        vector<mint> fib {1, 1};
        for (int i=2;i<sampleNum;i++) {
            fib.push_back(fib[i-1] + fib[i-2]);
        }
        return fib;
    };
    vector<mint> fib = calFib();

    std::function<vector<mint>()> calFirstNumbers = [&]() {
        vector<mint> res;
        mint cur = 0;
        for (int i=1;i<(int) fib.size();i++) {
            cur += fib[i] * mint(i).power(k);
            res.push_back(cur);
        }
        return res;
    };
    auto firstNumbers = calFirstNumbers();
    cout << getKthNumber<mint>(firstNumbers, n-1);

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
