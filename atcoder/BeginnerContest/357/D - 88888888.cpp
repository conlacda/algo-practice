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
    int n;
    cin >> n;
    int len = to_string(n).size();
    mint ans = 0;
    int anslen = 0;
    int b = n;
    mint cur = n;
    mint pow_anslen = mint(10).power(anslen);
    mint pow_len = mint(10).power(len);
    while (b > 0) {
        if (b & 1) {
            ans = ans + cur * pow_anslen;
            pow_anslen *= pow_len;
        }
        cur = cur * pow_len + cur;
        pow_len = pow_len * pow_len;
        b >>= 1;
    }
    cout << ans;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Bài này thuật toán gần tương tự như của binpow()
Xét từ binpow() trước
Ví dụ: binpow(3, 5) = 3 * 3 * 3 * 3 * 3;
                    = (3 * 3 * 3 *3) * 3;
                    = 3^4 * 3^1
Tách kết quả thành các số mũ tương ứng với dạng nhị phân của b. (5 = 101 -> 4 + 1 -> 3^4 * 3)
Ban đầu cur = 3^1, cứ sau mỗi vòng lặp thì cur = cur*cur để gấp đôi số mũ lên.
Nếu tại vị trí đó mà b tồn tại bit 1 (tức là b & 1 != 0) thì thêm cur vào kết quả sau cùng
cur = 3^1 -> b = 5 -> b & 1 != 0 -> ans *= cur;
cur = 3^2 -> b = 5 >> 1 = 2 (101 >> 1 -> 10) -> bit cuối là 0 ->  cur = 3^2 không xuất hiện trong kết quả
cur = 3^4 -> b = 2 >> 1 = 1 (10 >> 1 -> 1) -> bit cuối là 1 -> cur = 3^4 xuất hiện trong ans -> ans = ans * cur
b = 0 -> end

Tương tự tại bài này ta xét số x = 10
ans = 10101010101010101010 (10 lần 10)
Tương tự bài binpow() ta nhận thấy
cur = 10 -> sau mỗi lần cur = cur_cur (10_10) -> cur_cur_cur_cur = 10101010 ->...
ans cũng sẽ được tách thành các cụm 1010... dính liền nhau

cur ở bài trên = cur * cur -> ở đây là cur * 10^len + cur. 123123 = 123 * 10^3 + 123
tương tự nếu b ở đây ban đầu là n rồi dịch bit tương tự
ans = cur*10^len_ans+cur
Ví dụ ans = 123. Ta có kết quả sau cùng gồm 5 số 123 liền nhau
-> 123123123123_123.
Khi ans = 123, cur = 123123123123 thì sẽ dính cur vào trước ans thành 123_123_123_123_123
cur_ans = cur * 10^len_ans + ans
Ban đầu thì cứ để len_ans và len_cur dạng bình thường rồi tính thì mint(10).power(len) là ra kết quả
sau đó do power() khá chậm (OlogN) 1 thao tác nên mình có thể tính giữ luôn 10^len làm 1 biến.
*/
