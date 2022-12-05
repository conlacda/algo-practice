// https://codeforces.com/contest/727/submission/183991236
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

template <class Iterable> // chỉ chạy với 64bit.
class Hash {
  private:
    vector<ll> pc;
    ll factor = 137; // factor > num_of_character and is a prime.
    ll length;
    vector<ll> inv;
    Iterable s, rs;

  public:
    vector<ll> prefix_hash, rprefix_hash;
    char min_char = char(0);
    ll mod_inv(ll a) {
        ll x, y;
        auto extended_gcd = [&](ll a, ll b) -> ll {
            x = 1;
            y = 0;
            ll x1 = 0, y1 = 1, a1 = a, b1 = b;
            while (b1) {
                ll q = a1 / b1;
                tie(x, x1) = make_tuple(x1, x - q * x1);
                tie(y, y1) = make_tuple(y1, y - q * y1);
                tie(a1, b1) = make_tuple(b1, a1 - q * b1);
            }
            return a1;
        };
        ll g = extended_gcd(a, mod);
        if (g != 1)
            return -1;
        else
            x = (x % mod + mod) % mod;
        return x;
    }
    Hash() {}
    void build(ll length = 200005) {
        // Pre compute
        ll p = 1;
        for (ll i = 0; i < length; i++) {
            pc.push_back(p);
            p = (p * factor) % mod;
        }
        for (auto v : pc)
            inv.push_back(mod_inv(v));
    }
    ll once(Iterable s) {
        ll hash_value = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int v = s[i] - min_char + 1;
            hash_value = (hash_value + 1LL * v * pc[i]) % mod;
        }
        if (hash_value < 0)
            hash_value += mod;
        return hash_value;
    }
    ll ronce(Iterable s) {
        reverse(s.begin(), s.end());
        return once(s);
    }
    pair<ll, ll> both_once(Iterable s) { return make_pair(once(s), ronce(s)); }

    void load(Iterable s, bool reverse = false) {
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
        ll start = (!reverse) ? 0 : (ll)s.size() - 1;
        ll end = (!reverse) ? (ll)s.size() : -1;
        ll increment = (!reverse) ? 1 : -1;
        for (int i = start; i != end; i += increment) {
            int v = str->at(i) - min_char + 1;
            if (!reverse)
                hash_value = (hash_value + 1LL * v * pc[i]) % mod;
            else
                hash_value =
                    (hash_value + 1LL * v * pc[(int)s.size() - 1 - i]) % mod;
            ph->push_back(hash_value);
        }
    }
    void rload(Iterable s) {
        return load(s, true);
    } // alias for load(reverse=true);
    void both_load(Iterable s) {
        assert(inv.size() > 0); // quên chưa chạy hash.build()??
        load(s);
        rload(s);
    }
    // hash dạng rolling substr- tức là nếu start+length> s.size() thì sẽ vòng
    // lại lấy từ đầu đi tiếp
    ll substr(ll start, ll length) {
        assert(length <=
               (ll)s.size()); // assert(start+length <= (ll) s.size()); nếu chỉ
                              // muốn range thông thường ko phải dạng rolling
        ll ans = 0;
        if (start + length <= (ll)s.size()) {
            ans =
                (prefix_hash[start + length] - prefix_hash[start] + mod) % mod;
            return (ans * inv[start]) % mod;
        }
        ll start2ssize =
            (prefix_hash[s.size()] - prefix_hash[start] + mod) % mod;
        start2ssize = (start2ssize * inv[start]) % mod;
        ll zero2end = prefix_hash[length + start - (ll)s.size()];
        ans = (start2ssize + zero2end * pc[(ll)s.size() - start]) % mod;
        if (ans < 0)
            ans += mod;
        return ans;
    }
    ll rsubstr(ll start, ll length) {
        ll ans = 0;
        start = (ll)rs.size() - 1 - start;
        if (start + length <= (ll)rs.size()) {
            ans = (rprefix_hash[start + length] - rprefix_hash[start] + mod) %
                  mod;
            return (ans * inv[start]) % mod;
        }
        ll start2ssize =
            (rprefix_hash[(ll)rs.size()] - rprefix_hash[start] + mod) % mod;
        start2ssize = (start2ssize * inv[start]) % mod;
        ll zero2end = rprefix_hash[length + start - (ll)rs.size()];
        ans = (start2ssize + zero2end * pc[(ll)rs.size() - start]) % mod;
        if (ans < 0)
            ans += mod;
        return ans;
    }
    pair<ll, ll> both_substr(ll start, ll length) {
        ll end = (start + length >= (ll)s.size())
                     ? (start + length - (ll)s.size() - 1)
                     : (start + length - 1);
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
    ll n, k;
    cin >> n >> k;
    n = n * k;
    string s;
    cin >> s;
    ll q;
    cin >> q;
    Hash<string> hash;
    hash.build(s.size() + 5);
    hash.both_load(s);
    unordered_map<pair<ll, ll>, ll, IntPairHash> m; // hash value to index

    for (ll i = 0; i < q; i++) {
        string sub;
        cin >> sub;
        m[hash.both_once(sub)] = i + 1;
    }
    dbg(m);
    for (ll i = 0; i < k; i++) {
        ll end = (i + k >= n) ? (i + k - n - 1) : (i + k - 1);
        if (m.find(hash.both_substr(i, k)) == m.end()) {
            continue;
        }
        vector<ll> check; // chứa index
        check.push_back(m[hash.both_substr(i, k)]);
        ll start = i + k;
        if (start >= n)
            start -= n;
        while (start != i) {
            ll end = (start + k >= n) ? (start + k - n - 1) : (start + k - 1);
            if (m.find(hash.both_substr(start, k)) != m.end()) {
                check.push_back(m[hash.both_substr(start, k)]);
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

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
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