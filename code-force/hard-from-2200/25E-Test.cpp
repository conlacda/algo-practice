// https://codeforces.com/contest/25/submission/183992687
// https://codeforces.com/contest/25/problem/E
#include <bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

template<class Iterable>
class Hash{
private:
    vector<ll> pc;
    ll factor = 137;
    ll length;
    vector<ll> inv;
    Iterable s, rs;
public:
    vector<ll> prefix_hash, rprefix_hash;
    char min_char = char(0); // char(0) chạy với mọi thứ hoặc *min_element(s.begin(), s.end()); - cũ là 'a'
    ll mod_inv(ll a) { ll x, y;auto extended_gcd = [&] (ll a, ll b) -> ll { x = 1; y =0; ll x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) {ll q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1);tie(y, y1) = make_tuple(y1, y - q * y1);tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;};ll g = extended_gcd(a, mod);if (g != 1) return -1;else x = (x%mod +mod) %mod;return x;}
    Hash(){}
    void build(ll length = 200005){
        // Pre compute 
        ll p = 1;
        for (ll i=0;i<length;i++){
            pc.push_back(p);
            p = (p* factor) % mod;
        }
        for (auto v: pc) inv.push_back(mod_inv(v));
    }
    // Precompute O(N) dạng prefix sum để sau tính hash từ l->r với O(1). 
    void load(Iterable s, bool reverse = false){
        vector<ll> *ph;
        Iterable *str;
        if (!reverse) {
            str = &(this->s);
            ph = &prefix_hash;
        } else {
            str = &(this->rs);
            ph = &rprefix_hash;
        }
        *str = s;
        ph->resize(0);
        ph->push_back(0);
        ll hash_value = 0;
        ll start = (!reverse) ? 0 : (ll) s.size() -1;
        ll end = (!reverse) ? (ll) s.size() : -1;
        ll increment = (!reverse) ? 1 : -1;
        for (int i=start;i!=end;i+=increment){
            int v = str->at(i) - min_char + 1;
            if (!reverse) hash_value = (hash_value + 1LL*v*pc[i]) %mod;
            else hash_value = (hash_value + 1LL*v*pc[(int) s.size()-1-i]) %mod;
            ph->push_back(hash_value);
        }
    }
    void rload(Iterable s){ return load(s, true);} // alias for load(reverse=true);
    void both_load(Iterable s) {
        assert(inv.size() > 0); // quên chưa chạy hash.build()??
        load(s); rload(s);
    }
    // hash dạng rolling substr- tức là nếu start+length> s.size() thì sẽ vòng lại lấy từ đầu đi tiếp
    ll substr(ll start, ll length){
        assert(length <= (ll) s.size()); // assert(start+length <= (ll) s.size()); nếu chỉ muốn range thông thường ko phải dạng rolling
        ll ans = 0;
        if (start + length <= (ll) s.size()) {
            ans = (prefix_hash[start + length] - prefix_hash[start] + mod) % mod;
            return (ans * inv[start]) % mod;
        }
        ll start2ssize = (prefix_hash[s.size()] - prefix_hash[start] + mod) % mod;
        start2ssize = (start2ssize * inv[start]) % mod;
        ll zero2end = prefix_hash[length + start - (ll) s.size()];
        ans = (start2ssize + zero2end * pc[(ll) s.size() - start]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
    // Đoạn này có thể tách xừ ra thành 2 object Hash. reverse_hash(start, length) = hash(s.size()-1-start, length)
    // Nếu tách ra thì đoạn reverse và đoạn load sẽ gọn hơn và sau dễ chỉnh sửa hơn
    ll rsubstr(ll start, ll length){
        assert(length <= (ll) rs.size()); // assert(start+length <= (ll) rs.size()); nếu chỉ muốn range thông thường ko phải dạng rolling
        ll ans = 0;
        start = (ll) rs.size() - 1 - start;
        if (start + length <= (ll) rs.size()) {
            ans = (rprefix_hash[start + length] - rprefix_hash[start] + mod) % mod;
            return (ans * inv[start]) % mod;
        }
        ll start2ssize = (rprefix_hash[(ll) rs.size()] - rprefix_hash[start] + mod) % mod;
        start2ssize = (start2ssize * inv[start]) % mod;
        ll zero2end = rprefix_hash[length + start - (ll) rs.size()];
        ans = (start2ssize + zero2end * pc[(ll) rs.size() - start]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
    // Lấy ra luôn hash ngược và xuôi
    pair<ll, ll> both_substr(ll start, ll length){
        ll end = (start + length >= (ll) s.size()) ? (start + length - (ll) s.size() -1) : (start+length-1);
        return make_pair(substr(start, length), rsubstr(end, length)); 
    }
};
struct IntPairHash {
    static_assert(sizeof(int) * 2 == sizeof(size_t));
    size_t operator()(pair<ll, ll> p) const noexcept {
        return size_t(p.first) << 32 | p.second; // <<32 chỉ chạy với 64 bit.
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s1, s2, s3;
    Hash<string> hash;
    hash.build();
    // while (cin >> s1){
    cin >> s1 >> s2 >> s3;
    auto two_string = [&](string a, string b) -> string {
        Hash<string> ha = hash;
        ha.both_load(a);
        Hash<string> hb = hash;
        hb.both_load(b);
        ll ans = 0;
        for (ll i = min(a.size(), b.size()); i > 0; i--) {
            if (ha.both_substr(a.size() - i, i) == hb.both_substr(0, i)) {
                ans = i;
                break;
            }
        }
        return a + b.substr(min(ans, (ll)b.size()));
    };
    auto cal = [&](string s1, string s2, string s3) -> ll {
        return min(two_string(s1, two_string(s2, s3)).size(),
                   two_string(two_string(s1, s2), s3).size());
    };
    ll ans = LLONG_MAX;
    ans = min(ans, cal(s1, s2, s3));
    ans = min(ans, cal(s1, s3, s2));
    ans = min(ans, cal(s2, s1, s3));
    ans = min(ans, cal(s2, s3, s1));
    ans = min(ans, cal(s3, s2, s1));
    ans = min(ans, cal(s3, s1, s2));
    cout << ans;
    // }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Sometimes it is hard to prepare tests for programming problems. Now Bob is preparing tests to new problem about strings — input data to his problem is one string. Bob has 3 wrong solutions to this problem. The first gives the wrong answer if the input data contains the substring s1, the second enters an infinite loop if the input data contains the substring s2, and the third requires too much memory if the input data contains the substring s3. Bob wants these solutions to fail single test. What is the minimal length of test, which couldn't be passed by all three Bob's solutions?

Input
There are exactly 3 lines in the input data. The i-th line contains string si. All the strings are non-empty, consists of lowercase Latin letters, the length of each string doesn't exceed 105.

Output
Output one number — what is minimal length of the string, containing s1, s2 and s3 as substrings.

Examples
input
ab
bc
cd
output
4

input
abacaba
abaaba
x
output
11
*/