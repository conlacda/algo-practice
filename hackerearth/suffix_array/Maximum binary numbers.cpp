// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/suffix-arrays/practice-problems/algorithm/maximum-binary-number-2980dd7b/
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

struct SuffixArray{
private:
    const char min_char = 0x00; // kí tự 0 - gốc là $
    const int alphabet = 256;

    template<typename T> struct RMQ { int n = 0; vector<T> values; vector<vector<int>> range_low; bool maximum_mode = false; RMQ(const vector<T> &_values = {}) { if (!_values.empty()) build(_values); }  static int largest_bit(int x) { return x == 0 ? -1 : 31 - __builtin_clz(x); }   int better_index(int a, int b) const { return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;  }  void build(const vector<T> &_values) { values = _values; n = int(values.size()); int levels = largest_bit(n) + 1; range_low.resize(levels);  for (int k = 0; k < levels; k++) range_low[k].resize(n - (1 << k) + 1);  for (int i = 0; i < n; i++) range_low[0][i] = i;  for (int k = 1; k < levels; k++) for (int i = 0; i <= n - (1 << k); i++) range_low[k][i] = better_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]); }   int query_index(int a, int b) const { b++; assert(0 <= a && a < b && b <= n); int level = largest_bit(b - a); return better_index(range_low[level][a], range_low[level][b - (1 << level)]); }  T query_value(int a, int b) const { return values[query_index(a, b)]; } };
    vector<int> cal_suffix_array(string s){
        int n = s.size(); vector<int> p(n), c(n), cnt(max(alphabet, n), 0); for (int i = 0; i < n; i++) cnt[s[i]]++; for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i-1]; for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i; c[p[0]] = 0; int classes = 1; for (int i = 1; i < n; i++) { if (s[p[i]] != s[p[i-1]]) classes++; c[p[i]] = classes - 1;} vector<int> pn(n), cn(n); for (int h = 0; (1 << h) < n; ++h) { for (int i = 0; i < n; i++) { pn[i] = p[i] - (1 << h); if (pn[i] < 0) pn[i] += n;} fill(cnt.begin(), cnt.begin() + classes, 0); for (int i = 0; i < n; i++) cnt[c[pn[i]]]++; for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1]; for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i]; cn[p[0]] = 0; classes = 1; for (int i = 1; i < n; i++) { pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]}; pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]}; if (cur != prev) classes++; cn[p[i]] = classes - 1; } c.swap(cn);}
        p.erase(max_element(p.begin(), p.end())); // dấu $ - cũng là phần tử có index lớn nhất trong suffix_array (6* trong ví dụ dưới)
        return p;
    }
    vector<int> cal_lcp(){ vector<int> rank(n, 0), lcp(n-1, 0); for (int i = 0; i < n; i++) rank.at(suffix_array[i]) = i; int k = 0; for (int i = 0; i < n; i++) { if (rank[i] == n - 1) {k = 0; continue;} int j = suffix_array[rank[i] + 1]; while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++; lcp[rank[i]] = k; if (k) k--; } return lcp;  }
    
    RMQ<int> rmq_min_suf, rmq_max_suf;
    void build_rmq_on_suffix_array() { if (rmq_min_suf.values.size() == 0) rmq_min_suf.build(suffix_array); if (rmq_max_suf.values.size() == 0) { rmq_max_suf.maximum_mode = true; rmq_max_suf.build(suffix_array);}}
public:
    string s; int n;
    vector<int> suffix_array, lcp;
    RMQ<int> rmq_lcp; // just for common_prefix_of_substrs()
    vector<int> suf_to_indx; // index k có s.substr(k) ở vị trí bao nhiêu trong suffix_array.
    SuffixArray(string s){
        this->s = s; n = s.size();
        suffix_array = cal_suffix_array(s);
        lcp = cal_lcp();
        rmq_lcp.build(lcp); // just for common_prefix_of_substrs()
        build_rmq_on_suffix_array(); // sử dụng khi muốn query index min, max tại string ban đầu
        suf_to_indx.resize(n);
        for (int i=0;i<(int) suffix_array.size();i++) suf_to_indx[suffix_array[i]] = i;
    }
};

<hash-snippet>

void solve() {
    int n;
    int k;
    cin >> n >> k;
    string s;
    cin >> s;
    /*
    Cycle shift bao nhiêu lần thì tìm thấy số max lần thứ k
    khi này dùng binary search để lấy ra lower_bound, upper_bound
    -> lấy số dư + kết quả thứ k%n là xong
    */
    SuffixArray suf(s);
    int ind = suf.suffix_array[(int)s.size() - 1];
    string maxs = s.substr(ind) + s.substr(0, ind);
    Hash<string> hash;
    hash.build(s.size());
    hash.load(s);
    pair<ll, ll> maxh = hash.getHash(maxs);
    vector<ll> pos;
    for (ll i=0;i<(int)s.size();i++){
        if (hash.substr(i, (int)s.size()) == maxh){
            pos.push_back(i);
        }
    }
    dbg(pos);
    /*
    đi hết 1 vòng thì được pos.size() lần. Có k lần cần đi bao nhiêu vòng.
    */
    ll round = k / ((int) pos.size());
    ll step = k % (int) pos.size();
    if (step == 0){
        round--;
        step += (int) pos.size();
    }
    dbg(round, step);
    cout << round * (int) s.size() + pos[step-1]<<'\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    while (n--)
        solve();

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
0 10101
1 01011
2 10110
3 01101
4 11010
=>
1 01011
3 01101
0 10101
2 10110
4 11010
// Dùng hash để lấy ra danh sách các vị trí có giá trị bằng với max
// In ra kết quả

Bài này dùng suffix_array để tìm ra giá trị string lớn nhất trong cycle shift
Sau khi có string lớn nhất thì dùng Hash để xem các string nào bằng string lớn nhất đó.
pos[]  chứa vị trí index của string lớn nhất
Hỏi rằng bao nhiêu bước lặp qua pos thì đc k lần
-> pos = [1, 4, 5];
k = 5 -> [1, 4, 5], [1, 4] => đi mất 5(size) + 4 (pos[k-pos.size()-1])
*/

/*

Problem
A large binary number is represented by a string  of size  and comprises of  and . You must perform a cyclic shift on this string. The cyclic shift operation is defined as follows:

If the string  is , then after performing one cyclic shift, the string becomes .

You performed the shift infinite number of times and each time you recorded the value of the binary number represented by the string. The maximum binary number formed after performing (possibly ) the operation is . Your task is to determine the number of cyclic shifts that must be performed such that the value represented by the string  will be equal to  for the  time.

Input format

First line: A single integer  denotes the number of test cases
For each test case:
First line: Two space-separated integers  and 
Second line:  denotes the string
Output format

For each test case, print a single line containing one integer that represents the number of cyclic shift operations performed such that the value represented by string  is equal to  for the  time.

Constraints



, for each 

Note: The sum of  overall test cases is not exceeding .

Sample output  Sample output
2              9
5 2            3
10101
6 2
010101
*/

template<class Iterable> // chỉ chạy với 64bit.
class Hash{
private:
    vector<ll> pc;
    ll factor = 31; // factor > num_of_character and is a prime.
    ll length;
    vector<ll> inv;
    Iterable s, rs;
public:
    vector<ll> prefix_hash, rprefix_hash;
    char min_char = 'a'; // xem bảng ascii để lấy ra min_char. Ví dụ string có hoa thường, số -> min_char = '0'
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
        ans = (start2ssize + zero2end * pc[(ll) s.size() -start]) % mod;
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
        ans = (start2ssize + zero2end * pc[(ll) rs.size() -start]) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
    // Lấy ra luôn hash ngược và xuôi
    pair<ll, ll> both_substr(ll start, ll length){
        ll end = (start + length >= (ll) s.size()) ? (start + length - (ll) s.size() -1) : (start+length-1);
        return make_pair(substr(start, length), rsubstr(end, length)); 
    }

};

void solve() {
    int n;
    int k;
    cin >> n >> k;
    string s;
    cin >> s;
    /*
    Cycle shift bao nhiêu lần thì tìm thấy số max lần thứ k
    khi này dùng binary search để lấy ra lower_bound, upper_bound
    -> lấy số dư + kết quả thứ k%n là xong
    */
    SuffixArray suf(s);
    int ind = suf.suffix_array[(int)s.size() - 1];
    string maxs = s.substr(ind) + s.substr(0, ind);
    dbg(maxs);
    Hash<string> hash;
    hash.build(s.size()+5);
    hash.both_load(s);
    // pair<ll, ll> maxh = hash.both_substr(ind, (int) s.size());
    pair<ll, ll> maxh = hash.both_once(maxs);
    dbg(maxh);
    dbg(hash.both_substr(ind, (int) s.size()));
    vector<ll> pos;
    for (ll i=0;i<(int)s.size();i++){
        if (hash.both_substr(i, (int)s.size()) == maxh){
            pos.push_back(i);
        }
    }
    dbg(pos);
    /*
    đi hết 1 vòng thì được pos.size() lần. Có k lần cần đi bao nhiêu vòng.
    */
    ll round = k / ((int) pos.size());
    ll step = k % (int) pos.size();
    if (step == 0){
        round--;
        step += (int) pos.size();
    }
    dbg(round, step);
    cout << round * (int) s.size() + pos[step-1]<<'\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    while (n--)
        solve();

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
0 10101
1 01011
2 10110
3 01101
4 11010
=>
1 01011
3 01101
0 10101
2 10110
4 11010
// Dùng hash để lấy ra danh sách các vị trí có giá trị bằng với max
// In ra kết quả

Bài này dùng suffix_array để tìm ra giá trị string lớn nhất trong cycle shift
Sau khi có string lớn nhất thì dùng Hash để xem các string nào bằng string lớn nhất đó.
pos[]  chứa vị trí index của string lớn nhất
Hỏi rằng bao nhiêu bước lặp qua pos thì đc k lần
-> pos = [1, 4, 5];
k = 5 -> [1, 4, 5], [1, 4] => đi mất 5(size) + 4 (pos[k-pos.size()-1])
*/

/*

Problem
A large binary number is represented by a string  of size  and comprises of  and . You must perform a cyclic shift on this string. The cyclic shift operation is defined as follows:

If the string  is , then after performing one cyclic shift, the string becomes .

You performed the shift infinite number of times and each time you recorded the value of the binary number represented by the string. The maximum binary number formed after performing (possibly ) the operation is . Your task is to determine the number of cyclic shifts that must be performed such that the value represented by the string  will be equal to  for the  time.

Input format

First line: A single integer  denotes the number of test cases
For each test case:
First line: Two space-separated integers  and 
Second line:  denotes the string
Output format

For each test case, print a single line containing one integer that represents the number of cyclic shift operations performed such that the value represented by string  is equal to  for the  time.

Constraints



, for each 

Note: The sum of  overall test cases is not exceeding .

Sample output  Sample output
2              9
5 2            3
10101
6 2
010101
*/
