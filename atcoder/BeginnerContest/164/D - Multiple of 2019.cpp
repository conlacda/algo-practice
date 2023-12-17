// https://atcoder.jp/contests/abc164/tasks/abc164_d
// D - Multiple of 2019
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

const int maxN = 1000003;
template<unsigned int mod = mod>
struct mint {
    friend std::ostream& operator<<(std::ostream& os, const mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, mint &s) { return os >> s.x;}
    unsigned int x;
 
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
        x = (unsigned long long)x * a.x % mod;
        return *this;
    }
    mint& operator /= (const mint &a) {
        return *this *= a.inv();
    }

    mint power(ll pw) const {
        mint res = 1;
        mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string s;
    cin >> s;
    int n = (int) s.size();
    /*
    Tinh prefix chia cho 2019
    */
    mint<2019> cur = 0;
    map<mint<2019>, int> m;
    m[0]++;
    for (int i=n-1;i>=0;i--) {
        cur += mint<2019>(s[i] - '0') * mint<2019>(10).power(n-1-i);
        m[cur]++;
    }
    dbg(m);
    int ans =0;
    for (auto v: m){ 
        ans += (v.second-1) * v.second /2;
    }
    cout << ans;
    show_exec_time();
}
/*
Từ hàng đơn vị tính dần lên xem số dư của phần suffix cho 2019 là bao nhiêu
Ví dụ:
345678
-> 8 % 2019 => cur
-> 78 % 2019 = cur + 7 * pow(10, 1) -> cur
-> 678 % 2019 = cur + 6 * pow(10, 2) -> cur
-> 5678 % 2019 = cur + 5 * pow(10, 3) -> cur
-> 45678 % 2019 = cur + 4 * pow(10, 4) -> cur
2 số có cùng số dư khi chia cho 2019 -> s[l->r] chia hết cho 2019.
s[0->l] = 1, s[0->r] = 1 => s[l->r] = 0 khi chia cho 2019
*/
