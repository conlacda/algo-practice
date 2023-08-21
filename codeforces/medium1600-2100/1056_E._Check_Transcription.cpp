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
#endif

template<class Iterable> // chỉ chạy với 64bit.
class Hash {
private:
    const ll factor = 263; // số nguyên tố lớn hơn 255 - là full bảng Acsii
    const char min_char = 0x00; // kí tự 0
    vector<ll> inv, pc; // pre-compute
    ll n;
    // a*x ≡ 1 mod m -> find x - xem thêm tại math-compilation snippet
    ll mod_inv(ll a) { ll x, y;auto extended_gcd = [&] (ll a, ll b) -> ll { x = 1; y =0; ll x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) {ll q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1);tie(y, y1) = make_tuple(y1, y - q * y1);tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;};ll g = extended_gcd(a, mod);if (g != 1) return -1;else x = (x%mod +mod) %mod;return x;}
    int toInt(char x) { // char(127) = 127 nhưng char(128) = -127, ... char(255) = -1 
        int valOfChar = x - min_char + 1;
        int res = (valOfChar <= 0) ? valOfChar + 256 : valOfChar;
        assert(res > 0 && "min_char phải nhỏ hơn s[i]");
        return res;
    }
    int toInt(int x) {
        return x - min_char + 1;
    }
public:
    Iterable s;
    vector<ll> prefix_hash, suffix_hash;
    void build(ll length = 250000){ ll p = 1; for (ll i=0;i<length;i++){ pc.push_back(p); p = (p* factor) % mod;} for (auto v: pc) inv.push_back(mod_inv(v));}
    // Precompute O(N) dạng prefix sum để sau tính hash từ l->r với O(1).     
    void load(Iterable s) {
        assert((int) pc.size() >= (int) s.size() && "quên chưa hash.build()??");
        this->s = s; this->n = (ll) s.size();
        prefix_hash = suffix_hash = {0};
        ll pre = 0, suf = 0;
        for (int i=0;i< (int) s.size();i++) {
            pre = (pre + toInt(s[i]) * pc[i]) % mod;
            suf = (suf + toInt(s[(int) s.size() - i - 1]) * pc[i]) % mod;
            prefix_hash.push_back(pre);
            suffix_hash.push_back(suf);
        }
    }
    // Lấy ra hash của s.substr(start, length)
    ll substr(ll start, ll length) {
        assert(length <= n); // assert(start+length <= n); nếu chỉ muốn range thông thường ko phải dạng rolling
        ll end = (start + length >= n) ? (start + length - n -1) : (start+length-1);
        // hash dạng rolling substr- tức là nếu start+length> s.size() thì sẽ vòng lại lấy từ đầu đi tiếp
        std::function<int(ll, ll, vector<ll>&)> hashOfSubstr = [&](ll start, ll length, vector<ll>& ps_hash){
            ll ans = 0;
            if (start + length <= n) {
                ans = (ps_hash[start + length] - ps_hash[start] + mod) % mod;
                return (ans * inv[start]) % mod;
            }
            ll start2ssize = (ps_hash[n] - ps_hash[start] + mod) % mod;
            start2ssize = (start2ssize * inv[start]) % mod;
            ll zero2end = ps_hash[length + start - n];
            ans = (start2ssize + zero2end * pc[n - start]) % mod;
            if (ans < 0) ans += mod;
            return ans;
        };
        return (ll) hashOfSubstr(start, length, prefix_hash) << 32 | hashOfSubstr(n - 1 - end, length, suffix_hash);
    }
};
// http://localhost:3000/docs/competitive-programming/string/hash-string
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string t, s;
    cin >> t >> s;
    /*
    Dùng hash 1 cách thô bỉ để đếm
    */
    ll zero = 0, one = 0;
    for (auto v: t) {
        if (v == '0') {
            zero++;
        } else one++;
    }
    ll ans = 0;
    Hash<string> hash; hash.build(s.size());
    hash.load(s);

    std::function<bool(int, int)> check = [&](int a, int b){
        int cur = 0;
        ll hone = -1, hzero = -1;
        for (auto v: t){
            if (v == '0'){
                if (hzero == -1){
                    hzero = hash.substr(cur, a);
                } else {
                    if (hzero != hash.substr(cur, a)){
                        return false;
                    }
                }
                cur += a;
            } else {
                // v == 1
                if (hone == -1){
                    hone = hash.substr(cur, b);
                } else {
                    if (hone != hash.substr(cur, b)){
                        return false;
                    }
                }
                cur += b;
            }
        }
        dbg(hone, hzero);
        if (hzero == hone) return false;
        return true;
    };
    for (int i=1;i<= (int) s.size()/zero;i++){
        // s.size = i*zero + j*one;
        if ((s.size() - i*zero) % one !=0) continue;
        int j = (s.size() - i*zero) / one;
        if (j == 0) continue;
        if (check(i, j)) {
            ans++;
            dbg(i, j);
        }
    }
    cout << ans;
    /*
    Bài này chỉ đơn giản bruteforce với độ dài của 0 và độ dài của 1
    Xét độ dài của 0 là i, của 1 là j
    thế thì 0_num * i + 1_num *j == s.size()
    Với mỗi i ta tính ra j rồi dùng check(i, j) xem như thế có thỏa mãn không.
    */
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
