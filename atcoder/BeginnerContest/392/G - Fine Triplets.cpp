// https://atcoder.jp/contests/abc392/tasks/abc392_g
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

typedef complex<double> C;
// Chuyển coef sang value (các point trên mặt phẳng 2 chiều)
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
    vector<int> rev(n);
    for (int i=0;i<n;i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i=0;i<n;i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j=0;j<k;j++) {
                auto x = (double *)&rt[j + k];
                auto y = (double *)&a[i + j + k];
                C z(x[0] * y[0] - x[1] * y[1],
                    x[0] * y[1] + x[1] * y[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}

// Convolution without mod - lưu ý đầu vào là double
vector<double> conv(const vector<double>& a, const vector<double>& b) {
    if (a.empty() || b.empty()) return {};
    vector<double> res((int) a.size() + (int) b.size() - 1);
    int L = 32 - __builtin_clz((int) res.size()), n = 1 << L;
    vector<complex<double>> in(n), out(n);
    copy(a.begin(), a.end(), begin(in));
    for (int i=0;i<(int) b.size();i++)
        in[i].imag(b[i]);

    fft(in);
    for (auto& x : in) x *= x;
    for (int i=0;i<n;i++)
        out[i] = in[-i & (n - 1)] - conj(in[i]);
    
    fft(out);
    for (int i=0;i<(int) res.size();i++)
        res[i] = imag(out[i]) / (4 * n);
    return res;
}

template<int mod = mod>
vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    vector<ll> res((int) a.size() + (int) b.size() - 1);
    int B = 32 - __builtin_clz((int)res.size()), n = 1 << B, cut = (int)sqrt(mod);
    vector<C> L(n), R(n), outs(n), outl(n);
    for (int i=0;i<(int) a.size();i++) L[i] = C((int)a[i] / cut, (int)a[i] % cut);
    for (int i=0;i<(int) b.size();i++) R[i] = C((int)b[i] / cut, (int)b[i] % cut);
    // chuyển coef sang value trên mặt phẳng 2 chiều - O(NlogN) A, B => value
    fft(L), fft(R);
    // nhân value trong O(N) => value * value in O(N)
    for (int i=0;i<n;i++) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    // chuyển value đã nhân ngược trở lại thành coef => value sang C (A * B = C)
    fft(outl), fft(outs);
    for (int i=0;i<(int) res.size();i++) {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % mod * cut + bv) % mod * cut + cv) % mod;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    a - b = b - c
    => a + c = 2*b
    Nếu đưa a, c là hệ số của f(x) = x^a + x^c + ...
    rồi lấy f(x) * f(x) ta sẽ lấy được f(x)^2 = k*x^(a+c) + ...
    mọi số có tổng bằng a+c ví dụ a-1 + c+1 sẽ được nhóm vào x^(a+c) và số lượng tổng chỉnh là k
    -> với 1 số B bất kỳ, ta tính được số lượng cặp p<p1, p2> mà p1 + p2 = B
    Lấy b lặp qua toàn bộ S và ta tính kết quả = SUM(k1, k2, k3, ...) với ki là hệ số của 2*b trong f(x)^2
    */
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    dbg(a);
    sort(a.begin(), a.end());
    vector<int> fx((int) 1e6 + 5, 0);
    for (auto&v: a) fx[v] = 1;
    auto fx2 = convMod(fx, fx);
    dbg(fx2.size());
    int ans = 0;
    for (auto&v: a) {
        ans += (fx2[2 * v] - 1) / 2;
    }
    cout << ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
