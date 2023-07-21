#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 998244353; // 998244353  1000000009  1000000007
#define ld long double
#define int long long

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

vector<int> rev;
typedef complex<double> C;
void fft(vector<C> &a) {
    int n = (int) a.size(), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);  // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i=k;i<2*k;i++) {
            rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
        }   
    }
    
    for (int i=0;i<n;i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j=0;j<k;j++) {
                auto x = (double *)&rt[j + k];
                auto y = (double *)&a[i + j + k];
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}

template<int M = mod> vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> res((int) a.size() + (int) b.size() - 1);
    int B = 32 - __builtin_clz((int)res.size()), n = 1 << B, cut = (int)sqrt(M);
    vector<C> outs(n), outl(n);
    rev.resize(n); 
    for (int i=0;i<n;i++) rev[i] = (rev[i / 2] | (i & 1) << (31 - __builtin_clz(n))) / 2;
    std::function<void()> doFFT = [&](){
        vector<C> L(n), R(n);
        for (int i=0;i<(int) a.size();i++) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
        for (int i=0;i<(int) b.size();i++) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
        fft(L), fft(R);
        for (int i=0;i<n;i++) {
            int j = -i & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
        }
    };
    doFFT();
    fft(outl), fft(outs);
    for (int i=0;i<(int) res.size();i++) {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto &v: a) cin >> v;
    for (auto &v: b) cin >> v;
    auto ans = convMod(a, b);
    for (auto v: ans) cout << v << ' ';
    show_exec_time();
}