// https://codeforces.com/contest/271/problem/D
// Submission: https://codeforces.com/contest/271/submission/183965358
/*
You've got string s, consisting of small English letters. Some of the English letters are good, the rest are bad.

A substring s[l...r] (1 ≤ l ≤ r ≤ |s|) of string s  =  s1s2...s|s| (where |s| is the length of string s) is string  slsl + 1...sr.

The substring s[l...r] is good, if among the letters  sl, sl + 1, ..., sr there are at most k bad ones (look at the sample's explanation to understand it more clear).

Your task is to find the number of distinct good substrings of the given string s. Two substrings s[x...y] and s[p...q] are considered distinct if their content is different, i.e. s[x...y] ≠ s[p...q].

Input
The first line of the input is the non-empty string s, consisting of small English letters, the string's length is at most 1500 characters.

The second line of the input is the string of characters "0" and "1", the length is exactly 26 characters. If the i-th character of this string equals "1", then the i-th English letter is good, otherwise it's bad. That is, the first character of this string corresponds to letter "a", the second one corresponds to letter "b" and so on.

The third line of the input consists a single integer k (0 ≤ k ≤ |s|) — the maximum acceptable number of bad characters in a good substring.

Output
Print a single integer — the number of distinct good substrings of string s.

Examples
input
ababab
01000000000000000000000000
1
output
5
inputCopy
acbacbacaa
00000000000000000000000000
2
outputCopy
8
Note
In the first example there are following good substrings: "a", "ab", "b", "ba", "bab".

In the second example there are following good substrings: "a", "aa", "ac", "b", "ba", "c", "ca", "cb".
*/
#include<bits/stdc++.h>

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
class Hash{
private:
    vector<ll> pc;
    ll factor = 137;
    ll length;
    vector<ll> inv;
    Iterable s, rs;
public:
    vector<ll> prefix_hash, rprefix_hash;
    char min_char = char(0);
    ll mod_inv(ll a) { ll x, y;auto extended_gcd = [&] (ll a, ll b) -> ll { x = 1; y =0; ll x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) {ll q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1);tie(y, y1) = make_tuple(y1, y - q * y1);tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;};ll g = extended_gcd(a, mod);if (g != 1) return -1;else x = (x%mod +mod) %mod;return x;}
    Hash(){}
    void build(ll length = 200005){
        ll p = 1;
        for (ll i=0;i<length;i++){
            pc.push_back(p);
            p = (p* factor) % mod;
        }
        for (auto v: pc) inv.push_back(mod_inv(v));
    }

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
        ans = (start2ssize + zero2end * pc[(ll) s.size() -start]) % mod;
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
        ans = (start2ssize + zero2end * pc[(ll) rs.size() -start]) % mod;
        return ans;
    }
    pair<ll, ll> both_substr(ll start, ll length){
        ll end = (start + length >= (ll) s.size()) ? (start + length - (ll) s.size() -1) : (start+length-1);
        return make_pair(substr(start, length), rsubstr(end, length)); 
    }
};
struct IntPairHash {
    static_assert(sizeof(int) * 2 == sizeof(size_t));
    size_t operator()(pair<ll, ll> p) const noexcept {
        return size_t(p.first) << 32 | p.second;
    }
};


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string s; cin >> s;
    string ap; cin >> ap;
    map<char, int> m;
    for (int i=0;i<ap.size();i++){
        m['a' + i] = ap[i] - '0'; 
    }
    dbg(m);
    int k; cin >> k;
    std::unordered_map<pair<int,int>, bool, IntPairHash> hashed;
    int i=0, j =0;
    int bad = 0;
    Hash<string> hash;
    hash.build(s.size());
    hash.both_load(s);
    // Dùng 2 pointer để đếm số bad chars
    while (i<s.size()){
        if (m[s[i]] == 0) bad++;
        while (bad > k){
            if (m[s[j]] == 0) bad--;
            j++;
        }
        for (int z=j;z<=i;z++){
            dbg(hash.both_substr(z, i-z+1), s.substr(z, i-z+1));
            hashed[hash.both_substr(z, i-z+1)] = true;
        }
        i++;
    }
    dbg(hashed);
    cout << hashed.size();
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
