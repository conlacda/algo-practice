// https://codeforces.com/contest/1056/submission/183993406
// https://codeforces.com/contest/1056/problem/E
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
    ll factor = 137; // factor > num_of_character and is a prime.
    ll length;
    vector<ll> inv;
    Iterable s, rs;
public:
    vector<ll> prefix_hash, rprefix_hash;
    char min_char = char(0); // char(0) chạy với mọi thứ hoặc *min_element(s.begin(), s.end()); - cũ là 'a'
    // a*x ≡ 1 mod m -> find x - xem thêm tại math-compilation snippet
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
    ll once(Iterable s){
        ll hash_value = 0;
        for (int i=0;i< (int) s.size();i++){
            int v = s[i] - min_char + 1;
            hash_value = (hash_value + 1LL*v*pc[i]) % mod;
        }
        if (hash_value < 0) hash_value += mod;
        return hash_value; 
    }
    ll ronce(Iterable s){
        reverse(s.begin(), s.end()); // phần này viết giống dạng once nhanh hơn được 1 chút
        return once(s);
    }
    // lấy ra luôn 1 lúc hash ngược và hash xuôi
    pair<ll, ll> both_once(Iterable s){
        return make_pair(once(s), ronce(s));
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
    // so sánh 2 substring. 1,0,-1 tương ứng lớn, bằng, nhỏ hơn (chưa kiểm duyệt)
    ll compare_2substrs(ll st1, ll len1, ll st2, ll len2){ // s.substr(st1, len1) <=> s.substr(st1, len2)
        ll size = min(len1, len2);
        ll left = 0, right = size;
        while (left < right - 1){
            ll mid = (left + right) /2;
            if (substr(st1, st1 + mid) != substr(st2, st2 + mid)){
                right = mid-1;
            } else left = mid;
        }
        while (left < size && s[st1 + left] == s[st2 + left]) left++;
        if (left == size) {
            if (len1 > len2) return 1;
            else if (len1 < len2) return -1;
            else return 0;
        }
        if (s[st1 + left] > s[st2 + left]) return 1;
        else if (s[st1 + left] < s[st2 + left]) return -1;
        return 0;
    }
};
struct IntPairHash {
    static_assert(sizeof(int) * 2 == sizeof(size_t));
    size_t operator()(pair<ll, ll> p) const noexcept {
        return size_t(p.first) << 32 | p.second; // <<32 chỉ chạy với 64 bit.
    }
};

int main(){
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
    dbg(zero, one);
    ll ans = 0;
    Hash<string> hash; hash.build(s.size());
    hash.both_load(s);

    std::function<bool(int, int)> check = [&](int a, int b){
        int cur = 0;
        pair<ll, ll> hone = {-1, -1}, hzero = {-1, -1};
        for (auto v: t){
            if (v == '0'){
                if (hzero.first == -1){
                    hzero = hash.both_substr(cur, a);
                } else {
                    if (hzero != hash.both_substr(cur, a)){
                        return false;
                    }
                }
                cur += a;
            } else {
                // v == 1
                if (hone.first == -1){
                    hone = hash.both_substr(cur, b);
                } else {
                    if (hone != hash.both_substr(cur, b)){
                        return false;
                    }
                }
                cur += b;
            }
        }
        dbg(hone, hzero);
        if (hzero.first == hone.first && hzero.second == hone.second) return false;
        return true;
    };
    for (int i=1;i<=s.size()/zero;i++){
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
/*
One of Arkady's friends works at a huge radio telescope. A few decades ago the telescope has sent a signal s towards a faraway galaxy. Recently they've received a response t which they believe to be a response from aliens! The scientists now want to check if the signal t is similar to s.

The original signal s was a sequence of zeros and ones (everyone knows that binary code is the universe-wide language). The returned signal t, however, does not look as easy as s, but the scientists don't give up! They represented t as a sequence of English letters and say that t is similar to s if you can replace all zeros in s with some string r0 and all ones in s with some other string r1 and obtain t. The strings r0 and r1 must be different and non-empty.

Please help Arkady's friend and find the number of possible replacements for zeros and ones (the number of pairs of strings r0 and r1) that transform s to t.

Input
The first line contains a string s (2≤|s|≤105) consisting of zeros and ones — the original signal.

The second line contains a string t (1≤|t|≤106) consisting of lowercase English letters only — the received signal.

It is guaranteed, that the string s contains at least one '0' and at least one '1'.

Output
Print a single integer — the number of pairs of strings r0 and r1 that transform s to t.

In case there are no such pairs, print 0.

Examples
input
01
aaaaaa
output
4
input
001
kokokokotlin
output
2
Note
In the first example, the possible pairs (r0,r1) are as follows:

"a", "aaaaa"
"aa", "aaaa"
"aaaa", "aa"
"aaaaa", "a"
The pair "aaa", "aaa" is not allowed, since r0 and r1 must be different.

In the second example, the following pairs are possible:

"ko", "kokotlin"
"koko", "tlin"
*/