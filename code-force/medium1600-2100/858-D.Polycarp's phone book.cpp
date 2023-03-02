/*
Problem: https://codeforces.com/contest/858/problem/D
Submission: https://codeforces.com/contest/858/submission/195474086
There are n phone numbers in Polycarp's contacts on his phone. Each number is a 9-digit integer, starting with a digit different from 0. All the numbers are distinct.

There is the latest version of Berdroid OS installed on Polycarp's phone. If some number is entered, is shows up all the numbers in the contacts for which there is a substring equal to the entered sequence of digits. For example, is there are three phone numbers in Polycarp's contacts: 123456789, 100000000 and 100123456, then:

if he enters 00 two numbers will show up: 100000000 and 100123456,
if he enters 123 two numbers will show up 123456789 and 100123456,
if he enters 01 there will be only one number 100123456.
For each of the phone numbers in Polycarp's contacts, find the minimum in length sequence of digits such that if Polycarp enters this sequence, Berdroid shows this only phone number.

Input
The first line contains single integer n (1 ≤ n ≤ 70000) — the total number of phone contacts in Polycarp's contacts.

The phone numbers follow, one in each line. Each number is a positive 9-digit integer starting with a digit from 1 to 9. All the numbers are distinct.

Output
Print exactly n lines: the i-th of them should contain the shortest non-empty sequence of digits, such that if Polycarp enters it, the Berdroid OS shows up only the i-th number from the contacts. If there are several such sequences, print any of them.

Example:
inp:
3
123456789
100000000
100123456
out:
9
000
01

inp:
4
123456789
193456789
134567819
934567891
out:
2
193
81
91
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
#define destructure(a) #a
#endif

// Full doc: https://github.com/conlacda/algo-learning/blob/master/string/cp-algorithm/hash-full.md
template<class Iterable> // chỉ chạy với 64bit.
class Hash{
private:
    vector<ll> pc; // pre-compute 
    ll factor = 137; // **
    vector<ll> inv;
    Iterable s, rs;
public:
    vector<ll> prefix_hash, rprefix_hash;
    char min_char = char(0); // **
    // a*x ≡ 1 mod m -> find x - xem thêm tại math-compilation snippet
    ll mod_inv(ll a) { ll x, y;auto extended_gcd = [&] (ll a, ll b) -> ll { x = 1; y =0; ll x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) {ll q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1);tie(y, y1) = make_tuple(y1, y - q * y1);tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;};ll g = extended_gcd(a, mod);if (g != 1) return -1;else x = (x%mod +mod) %mod;return x;}
    void build(ll length = 200005){ ll p = 1; for (ll i=0;i<length;i++){ pc.push_back(p); p = (p* factor) % mod;} for (auto v: pc) inv.push_back(mod_inv(v));}
    // lấy ra luôn 1 lúc hash ngược và hash xuôi
    pair<ll, ll> hash(Iterable s){
        std::function<ll(Iterable)> hash_oneway_toward = [&](Iterable s){
            ll hash_value = 0;
            for (int i=0;i< (int) s.size();i++){
                int v = s[i] - min_char + 1;
                hash_value = (hash_value + 1LL*v*pc[i]) % mod;
            }
            if (hash_value < 0) hash_value += mod;
            return hash_value; 
        };
        ll hsh_toward = hash_oneway_toward(s);
        reverse(s.begin(), s.end());
        ll hsh_backward = hash_oneway_toward(s);
        return {hsh_toward, hsh_backward};
    }

    // Precompute O(N) dạng prefix sum để sau tính hash từ l->r với O(1). 
    void load_toward(Iterable s, bool reverse = false){
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
    void load_backward(Iterable s){ return load_toward(s, true);} // alias for load(reverse=true);
    void load(Iterable s) {
        assert(pc.size() > 0); // quên chưa chạy hash.build()??
        load_toward(s); load_backward(s);
    }
    // hash dạng rolling substr- tức là nếu start+length> s.size() thì sẽ vòng lại lấy từ đầu đi tiếp
    ll substr_toward(ll start, ll length){
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
    ll substr_backward(ll start, ll length){
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
    // Lấy ra hash của s.substr(start, length)
    pair<ll, ll> substr(ll start, ll length) {
        ll end = (start + length >= (ll) s.size()) ? (start + length - (ll) s.size() -1) : (start+length-1);
        return make_pair(substr_toward(start, length), substr_backward(end, length));
    }
    // so sánh 2 substring. 1,0,-1 tương ứng lớn, bằng, nhỏ hơn (chưa kiểm duyệt)
    ll compare_2substrs(ll st1, ll len1, ll st2, ll len2){ // s.substr(st1, len1) <=> s.substr(st1, len2)
        ll size = min(len1, len2);
        ll left = 0, right = size;
        while (left < right - 1){
            ll mid = (left + right) /2;
            if (substr_toward(st1, st1 + mid) != substr_toward(st2, st2 + mid)){
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

/*
Hash<string> hash; Hash<vector<int>> hash; hash.build(); || hash.build(s.size());
hash.hash(string); // hash 1 lần cho string và reversed_string
// Hash nhiều lần dạng query hash cho 1 range bất kỳ O(N) cho build và O(1) cho query
hash.load(s); 
hash.substr(start, length); // hash vòng tròn. "abcd" -> substr(2,3) = {substr(cda), substr(adc)}
unordered_map<pair<ll, ll>, bool, IntPairHash> m; // map<pair<ll, ll>, bool> m; có thể dùng trực tiếp nhưng tốc độ cực chậm (x2)
m[hash.hash(s)] = true;
m[hash.substr(start, length)] = true;
m.find(hash.hash(sub)) == m.end() | != m.end();
*/

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    // Dùng hash để check brute-force
    int n;
    cin >> n;
    vector<string> a(n);
    string s = "";
    for (int i=0;i<n;i++) cin >> a[i];
    Hash<string> hash;
    // xử lý từng trường string 1 -> 1 string tạo ra 81 mã hash
    // Đếm tất cả mã hash đó vào 1 map -> xét lại từng substring xem nếu có số hash == 1 là được
    hash.build(10);
    vector<unordered_set<pair<ll, ll>, IntPairHash>> v(n);
    // v tại đây lấy ra 81hash của string ith đưa ra set, giống nhau sẽ bị xóa
    for (int i=0;i<n;i++) {
        hash.load(a[i]);
        for (int j=0;j<9;j++) {
            for (int k=j;k<9;k++) {
                v[i].insert(hash.substr(j, k-j+1));
            }
        }
    }
    // hợp tất cả v vào trong m và đếm xem hash xuất hiện mấy lần
    // Do v là vector<set> nên ở đây bất kỳ hash nào xuất hiện >=2 là do xuất hiện ở 2 string khác nhau
    // -> chỉ cần xuất hiện 1 lần thì đó chính là duy nhất và cập nhật lại ans nếu độ dài nó ngắn hơn so với độ dài hiện tại
    unordered_map<pair<ll, ll>, ll, IntPairHash> m;
    for (int i=0;i<n;i++){
        for (auto u: v[i]){
            m[u]++;
        }
    }
    vector<string> ans(n, "____________________"); // dài nhất là 9 phần tử là khi gõ toàn bộ số điện thoại -> ____ chỉ làm mẫu để nó có độ dài > 9
    for (int i=0;i<n;i++) {
        hash.load(a[i]);
        for (int j=0;j<9;j++){
            for (int k=j;k<9;k++){
                if (m[hash.substr(j, k-j+1)] == 1) {
                    if (ans[i].size() > k-j+1) {
                        ans[i] = a[i].substr(j, k-j+1);
                    }
                }
            }
        }
    }
    for (auto v: ans) {
        cout << v << '\n';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
