// https://codeforces.com/contest/727/submission/195569516
// https://codeforces.com/contest/727/problem/E
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
    // lấy ra luôn 1 lúc hash ngược và hash xuôi
    ll getHash(Iterable s){
        assert((int) pc.size() >= (int) s.size() && "quên chưa hash.build()??");
        std::function<int(Iterable)> getHash1Way = [&](Iterable s){
            ll hash_value = 0;
            for (int i=0;i< (int) s.size();i++) 
                hash_value = (hash_value + toInt(s[i]) * pc[i]) % mod;
            if (hash_value < 0) hash_value += mod;
            return hash_value; 
        };
        int hsh_fwd = getHash1Way(s);
        reverse(s.begin(), s.end());
        int hsh_bwd = getHash1Way(s);
        return (ll) hsh_fwd << 32 | hsh_bwd;
    }
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
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll n, k;
    cin >> n >> k;
    n = n * k;
    string s;
    cin >> s;
    ll q;
    cin >> q;
    Hash<string> hash;
    hash.build(s.size() + 5);
    hash.load(s);
    unordered_map<ll, ll> m; // hash value to index

    for (ll i = 0; i < q; i++) {
        string sub;
        cin >> sub;
        m[hash.getHash(sub)] = i + 1;
    }
    dbg(m);
    for (ll i = 0; i < k; i++) {
        if (m.find(hash.substr(i, k)) == m.end()) {
            continue;
        }
        vector<ll> check; // chứa index
        check.push_back(m[hash.substr(i, k)]);
        ll start = i + k;
        if (start >= n)
            start -= n;
        while (start != i) {
            if (m.find(hash.substr(start, k)) != m.end()) {
                check.push_back(m[hash.substr(start, k)]);
                start += k;
                if (start >= n)
                    start -= n;
            } else
                break;
        }
        if (start == i) {
            unordered_set<ll> sc(check.begin(), check.end());
            if (sc.size() == check.size()) {
                cout << "YES\n";
                for (auto v : check) {
                    cout << v << ' ';
                }
                return 0;
            }
        }
    }
    cout << "NO\n";
}
/*
Several years ago Tolya had n computer games and at some point of time he decided to burn them to CD. After that he wrote down the names of the games one after another in a circle on the CD in clockwise order. The names were distinct, the length of each name was equal to k. The names didn't overlap.

Thus, there is a cyclic string of length n·k written on the CD.

Several years have passed and now Tolya can't remember which games he burned to his CD. He knows that there were g popular games that days. All of the games he burned were among these g games, and no game was burned more than once.

You have to restore any valid list of games Tolya could burn to the CD several years ago.

Input
The first line of the input contains two positive integers n and k (1 ≤ n ≤ 105, 1 ≤ k ≤ 105) — the amount of games Tolya burned to the CD, and the length of each of the names.

The second line of the input contains one string consisting of lowercase English letters — the string Tolya wrote on the CD, split in arbitrary place. The length of the string is n·k. It is guaranteed that the length is not greater than 106.

The third line of the input contains one positive integer g (n ≤ g ≤ 105) — the amount of popular games that could be written on the CD. It is guaranteed that the total length of names of all popular games is not greater than 2·106.

Each of the next g lines contains a single string — the name of some popular game. Each name consists of lowercase English letters and has length k. It is guaranteed that the names are distinct.

Output
If there is no answer, print "NO" (without quotes).

Otherwise, print two lines. In the first line print "YES" (without quotes). In the second line, print n integers — the games which names were written on the CD. You should print games in the order they could have been written on the CD, it means, in clockwise order. You can print games starting from any position. Remember, that no game was burned to the CD more than once. If there are several possible answers, print any of them.
input
3 1
abc
4
b
a
c
d
output
YES
2 1 3 

input
4 2
aabbccdd
4
dd
ab
bc
cd
output
NO
*/
